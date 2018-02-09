#include "clang/ASTMatchers/ASTMatchFinder.h"
//#include "clang/ASTMatchers/ASTMatchers.h"
//#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/CommandLine.h"

/*using namespace clang::ast_matchers;*/
/*using namespace clang::tooling;*/
/*using namespace clang;*/
/*using namespace llvm;*/

class MyPrinter :
    public clang::ast_matchers::MatchFinder::MatchCallback
{
public:
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result)
    {
        clang::ASTContext *Context = Result.Context;
        if (const clang::CallExpr *E =
            Result.Nodes.getNodeAs<clang::CallExpr>("functions"))
        {
            clang::FullSourceLoc FullLocation = Context->getFullLoc(E->getLocStart());
            if (FullLocation.isValid())
            {
                llvm::outs() << "Found call at "
                             << FullLocation.getSpellingLineNumber() << ":"
                             << FullLocation.getSpellingColumnNumber() << "\n";
            }
        }
    }
};

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static llvm::cl::extrahelp MoreHelp("\nMore help text...");

int main(int argc, const char **argv)
{
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());

    MyPrinter Printer;
    clang::ast_matchers::MatchFinder Finder;

    clang::ast_matchers::StatementMatcher functionMatcher =
      clang::ast_matchers::callExpr(clang::ast_matchers::callee(clang::ast_matchers::functionDecl(clang::ast_matchers::hasName("doSomething")))).bind("functions");

    Finder.addMatcher(functionMatcher, &Printer);

    return Tool.run(clang::tooling::newFrontendActionFactory(&Finder).get());
}
