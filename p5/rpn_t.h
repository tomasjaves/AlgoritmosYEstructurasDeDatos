// AUTOR: Tomás Javes Tommasone
// FECHA: 10/04/2023
// EMAIL: alu0101515458@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 5
// ESTILO: Google C++ Style Guide
// COMENTARIOS: Clase RPN (Reverse Polish Notation)

#ifndef RPNT_H_
#define RPNT_H_

#include <iostream>
#include <cctype>
#include <cmath>
//#include <cstdlib>

#include "queue_l_t.h"

// Clase RPN (Reverse Polish Notation)
template <class T> class rpn_t {
 public:
  // constructor
  rpn_t(void) : stack_() {}

  // destructor
  ~rpn_t() {}

  // operaciones
  const int evaluate(queue_l_t<char>&);

 private: 
  T stack_;
  void operate_(const char operador);
};


// operaciones
template<class T> const int rpn_t<T>::evaluate(queue_l_t<char>& q) {
  while (!q.empty()) 	{
    char c = q.front();
    
    q.pop();
    std::cout << "Sacamos de la cola un carácter: " << c;

    if (isdigit(c)) {
      int i = c - '0'; // Para convertir caracter digito en un valor numerico equivalente.
      std::cout << " (es un dígito) " << std::endl
<< "   Lo metemos en la pila..." << std::endl;
      stack_.push(i);
    } else {
      std::cout << " (es un operador)" << std::endl;
      operate_(c);
    }
  }
  return stack_.top();
}

template<class T> void rpn_t<T>::operate_(const char c) {
  assert(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'r' || c == 'l' || c == 'c');
  int result = 0;
  int valor = stack_.top();
  stack_.pop();
  std::cout << "   Sacamos de la pila un operando: " << valor << std::endl;
  if(c == 'r' || c == 'l' || c == 'c') {
    switch (c) {
    case 'r':
      result = sqrt(valor);
      break;
    case 'l':
      result = log2(valor);
      break;
    case 'c':
      result = pow(valor,2);
      break;
    }
  } else {
    int valor2 = stack_.top();
    stack_.pop();
    std::cout << "   Sacamos de la pila otro operando: " << valor2 << std::endl;
    
    switch (c) {
      case '+':
        result = valor2+valor;
        break;
      case '-':
        result = valor2-valor;
        break;
      case '*':
        result = valor*valor2;
        break;
      case '/':
        result = valor2/valor;
        break;
      case '^':
        result = pow(valor2,valor);
        break;
    }
  }

  stack_.push(result);
  std::cout << "   Metemos en la pila el resultado: ";
  std::cout << result << std::endl;
}

 
#endif  // RPNT_H_
