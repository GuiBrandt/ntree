# ntree
Implementação de árvore n-ária de busca genérica em C++

Feito como exercício nas aulas do Prof. André (a.k.a. Maligno) no 6º 
semestre do curso de Informática no COTUCA.

## Primeiros passos

### Para testar
Para compilar os testes, use [`make`](https://www.gnu.org/software/make/).

No Linux:
```
$ make
```

No Windows:
```
> make win32
```

Será gerado um arquivo `tests/all` (ou `tests/all.exe`, no Windows) que executa
os testes unitários necessários usando o [`googletest`](https://github.com/google/googletest).

### Para usar
Para usar a classe de árvore n-ária de busca no seu projeto, copie o arquivo
`ntree.hpp` para a pasta do seu projeto e, no código, inclua o cabeçalho:
```cpp
#include "ntree.hpp"
```