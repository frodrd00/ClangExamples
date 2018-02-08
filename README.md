# Clang
# Introducción a clang-AST

Este proyecto contiene tres ejemplos diferentes sobre cómo utilizar clang: dos con LibTooling y uno con LibClang. En los tres casos el ejemplo imprime cierta información (número de línea y de columna) cada vez que se realiza una llamada a una función denominada "doSomething". Todos los ejemplos se pueden compilar de dos maneras: (1) utilizando CMake o (2) compilando manualmente el ejemplo.

## Contenidos del proyecto

| Fichero                             | Descripción                                        |
| ----------------------------------- | -------------------------------------------------- |
| ./readme.md                         | Fichero de ayuda                                   |
| ./src/libtooling_example_tool_1.cpp | Ejemplo de LibTooling mediante RecursiveASTVisitor |
| ./src/libtooling_example_tool_2.cpp | Ejemplo de LibTooling mediante ASTMatchers         |
| ./src/libclang_example_tool.cpp     | Ejemplo de LibClang mediante cursores              |
| ./src/CMakeLists.txt                | Script para compilar los ejemplos con CMake        |
| ./input/example.cpp                 | Ejemplo de código fuente para analizar             |
| ./input/example_2.cpp               | Otro ejemplo de ćodigo fuente para analizar        |

## Compilación

### CMake

En el caso de usar CMake es necesario modificar el fichero *CMakeLists.txt* para sustituir, en las líneas correspondientes, el fichero que se desea compilar. A continuación se deberán introducir los siguientes comandos:

```
export CXX=/usr/local/bin/clang++
mkdir -p build
cd build
cmake ..
make
```

### Compilación manual

En todos los casos habrá que sustituir *nombre_fichero_ejemplo* por el fichero correspondiente. Previamente, crearemos un directorio para almacenar los ficheros ejecutables:

```
mkdir -p bin
```

#### LibTooling

```
clang++ $(llvm-config --cxxflags --ldflags) nombre_fichero_ejemplo.cpp \
-lclangTooling -lclangFrontendTool -lclangFrontend -lclangDriver \
-lclangSerialization -lclangParse -lclangSema -lclangStaticAnalyzerCheckers \
-lclangStaticAnalyzerCore -lclangAnalysis -lclangRewriteFrontend -lclangEdit \
-lclangASTMatchers -lclangAST -lclangLex -lclangBasic -lclang \
$(llvm-config --libs --system-libs) -o ./bin/nombre_fichero_ejemplo
```

#### LibClang

```
clang++ nombre_fichero_ejemplo.cpp -std=c++11 -g \
-I/usr/local/include/llvm -L/usr/local/lib -lclang \
-o ./bin/nombre_fichero_ejemplo
```

### Ejecución

En todos los casos la ejecución es similar:

```
./bin/nombre_fichero_ejemplo ../input/example_2.cpp
```