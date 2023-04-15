// AUTOR: Tomás Javes Tommasone
// FECHA: 27/03/2023
// EMAIL: alu0101515458@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Campo data_ de SllPolynomial
typedef sll_node_t<pair_double_t> SllPolyNode;  // Nodos de SllPolynomial

// Clase para polinomios basados en listas simples de pares
class SllPolynomial : public sll_t<pair_double_t> {
 public:
  // constructores
  SllPolynomial(void) : sll_t() {};
  SllPolynomial(const vector_t<double>&, const double = EPS);

  // destructor
  ~SllPolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SllPolynomial&, const double = EPS) const;
  void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);

  // MODIFICACION
  SllPolynomial Modify(SllPolynomial);
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

// FASE II
// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps) {
  bool first = true; // Utilizamos un condicional para saber si es el primer nodo.
  sll_node_t<pair_double_t>* aux_ptr = nullptr; // Creamos un puntero auxiliar que sirva para recorrer la lista.

  for(int i = v.get_size()-1; i >= 0; --i) { // Recorremos el vector dado.
    if(!first && fabs(v.at(i)) >= eps) { // Si no es el primer nodo y no es cero.
      pair_double_t aux(v.at(i), i); // Creamos un auxiliar pair que almacene el valor y el índice.
      insert_after(aux_ptr, new sll_node_t<pair_double_t>(aux)); // Metemos en la lista el nodo posterior al nodo correspondiente.
      aux_ptr = aux_ptr->get_next(); // El puntero auxiliar se posiciona en el siguiente del que se le había asignado.
    }
    if(first && fabs(v.at(i)) >= eps) { // Si no es el primer nodo y no es cero.
      pair_double_t aux(v.at(i), i); // Creamos un auxiliar pair que almacene el valor y el índice.
      push_front(new sll_node_t<pair_double_t>(aux)); // Metemos en la lista un nuevo nodo head con los valores obtenidos anteriormente.
      aux_ptr = get_head(); // Utilizamos un puntero auxiliar que nos permita operar con los siguientes nodos.
      first = false; // Asignamos false a first puesto que hemos abarcado el primer nodo. Todos los demás son posteriores al primero.
    }
  }
}


// E/S
void SllPolynomial::Write(std::ostream& os) const {
  os << "[ ";
  bool first{true};
  SllPolyNode* aux{get_head()};
  while (aux != NULL) {
    int inx{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    if (val > 0)
      os << (!first ? " + " : "") << val;
    else
      os << (!first ? " - " : "-") << fabs(val);
    os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
    aux = aux->get_next();
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SllPolynomial& p) {
  p.Write(os);
  return os;
}


// Operaciones con polinomios

// FASE III
// Evaluación de un polinomio representado por lista simple
double SllPolynomial::Eval(const double x) const {
  double result{0.0};
  double exp = 0.f; // Creamos una variable para almacenar el resultado del numero elevado.
  sll_node_t<pair_double_t>* aux_ptr = get_head(); // Creamos un puntero para recorrer la lista.

  while(aux_ptr != nullptr) { // Mientras el puntero no sea nulo.
    exp = pow(x, aux_ptr->get_data().get_inx()); // Elevamos el numero a su correspondido indice.
    result += aux_ptr->get_data().get_val() * exp; // Multiplicamos el valor obtenido al valor del nodo y lo sumamos en result.
    aux_ptr = aux_ptr->get_next(); // Movemos el puntero al siguiente nodo.
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol,
			    const double eps) const {
  bool differents = false;
  int contador1 = 0, contador2 = 0; // Creamos dos contadores para verificar las longitudes de los polinomios.
  sll_node_t<pair_double_t>* aux_ptr = this->get_head(); // Creamos un puntero que apunte a la primera lista.
  sll_node_t<pair_double_t>* aux_ptr2 = sllpol.get_head(); // Creamos un puntero que apunte a la segunda lista.
  while(aux_ptr != nullptr) { // Mientras el puntero de la primera lista no sea null.
    ++contador1; // Sumamos uno a contador1.
    aux_ptr = aux_ptr->get_next(); // Movemos el puntero al siguiente nodo.
  }
  while(aux_ptr2 != nullptr) { // Mientras el puntero de la segunda lista no sea null.
    ++contador2; // Sumamos uno a contador2.
    aux_ptr2 = aux_ptr2->get_next(); // Movemos el puntero al siguiente nodo.
  }
  if(contador1 != contador2) return differents; // Si ambos contadores son diferentes significa que los tamanios son distintos.
  aux_ptr = get_head(); // Asignamos el puntero de la primera lista a la cabeza de ella.
  aux_ptr2 = sllpol.get_head(); // Asignamos el puntero de la segunda lista a la cabeza de ella.
  while(aux_ptr != nullptr) { // Mientras cualquiera de los dos punteros no sea null.
    if(aux_ptr->get_data().get_inx() != aux_ptr2->get_data().get_inx()) return differents; // Verificamos si los indices son iguales.
    if(aux_ptr->get_data().get_val() != aux_ptr2->get_data().get_val()) return differents; // Verificamos si los valores son iguales.
    aux_ptr = aux_ptr->get_next(); // Movemos el puntero de la primera lista al siguiente nodo.
    aux_ptr2 = aux_ptr2->get_next(); // Movemos el puntero de la segunda lista al siguiente nodo.
  }
  return !differents;
}

// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
void SllPolynomial::Sum(const SllPolynomial& sllpol,
			SllPolynomial& sllpolsum,
			const double eps) {
  sll_node_t<pair_double_t>* aux_ptr = get_head(); // Creamos un puntero que apunte a la cabeza de la primera lista.
  sll_node_t<pair_double_t>* aux_ptr2 = sllpol.get_head(); // Creamos un puntero que apunte a la cabeza de la segunda lista.
  sll_node_t<pair_double_t>* aux_ptr_sum = nullptr; // Creamos un puntero para la lista suma.

  while(aux_ptr != nullptr && aux_ptr2 != nullptr) { // Mientras los punteros de las listas a sumar no sean null.
    if(aux_ptr->get_data().get_inx() == aux_ptr2->get_data().get_inx()) { // Si tienen el mismo indice.
      pair_double_t aux_pair(aux_ptr->get_data().get_val() + aux_ptr2->get_data().get_val(),
                             aux_ptr->get_data().get_inx()); // Asignamos un pair con la suma de los valores de
                                                             // los nodos y el indice.
      if(!sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps) { // Si la lista suma no está vacía y el valor sumado no es 0.
        sllpolsum.insert_after(aux_ptr_sum, new sll_node_t<pair_double_t>(aux_pair)); // Colocamos el nodo posterior al último.
        aux_ptr_sum = aux_ptr_sum->get_next(); // El puntero de la lista suma apunta al nuevo nodo.
      }
      if(sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps){ // Si la lista suma está vacía y el valor sumado no es 0.
        sllpolsum.push_front(new sll_node_t<pair_double_t>(aux_pair)); // Colocamos el primer nodo en la lista.
        aux_ptr_sum = sllpolsum.get_head(); // El puntero de la lista suma apunta al primer nodo.
      }        
      aux_ptr = aux_ptr->get_next(); // Movemos el puntero de la primera lista al siguiente nodo.
      aux_ptr2 = aux_ptr2->get_next(); // Movemos el puntero de la segunda lista al siguiente nodo.
    } else if(aux_ptr->get_data().get_inx() > aux_ptr2->get_data().get_inx()) { // Si el índice de la primera lista es mayor.
      pair_double_t aux_pair(aux_ptr->get_data().get_val(), aux_ptr->get_data().get_inx());
        if(!sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps) {
          sllpolsum.insert_after(aux_ptr_sum, new sll_node_t<pair_double_t>(aux_pair));
          aux_ptr_sum = aux_ptr_sum->get_next();
        }
        if(sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps){
          sllpolsum.push_front(new sll_node_t<pair_double_t>(aux_pair));
          aux_ptr_sum = sllpolsum.get_head();
        }
        aux_ptr = aux_ptr->get_next(); // Movemos unicamente el puntero de la primera lista al siguiente nodo.
    } else { // Si el puntero de la segunda lista es mayor.
      pair_double_t aux_pair(aux_ptr2->get_data().get_val(), aux_ptr2->get_data().get_inx());
        if(!sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps) {
          sllpolsum.insert_after(aux_ptr_sum, new sll_node_t<pair_double_t>(aux_pair));
          aux_ptr_sum = aux_ptr_sum->get_next();
        }
        if(sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps){
          sllpolsum.push_front(new sll_node_t<pair_double_t>(aux_pair));
          aux_ptr_sum = sllpolsum.get_head();
        }
        aux_ptr2 = aux_ptr2->get_next(); // Movemos unicamente el puntero de la segunda lista al siguiente nodo.
    }
  }

if(aux_ptr != nullptr && aux_ptr2 == nullptr) { // Si el puntero de la primera lista no es null pero el segundo si,
                                                // metemos todos los valores sobrantes de la primera lista en lista suma.
  while(aux_ptr != nullptr) {
    pair_double_t aux_pair(aux_ptr->get_data().get_val(), aux_ptr->get_data().get_inx());
    if(!sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps) {
      sllpolsum.insert_after(aux_ptr_sum, new sll_node_t<pair_double_t>(aux_pair));
      aux_ptr_sum = aux_ptr_sum->get_next();
    }
    if(sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps){
      sllpolsum.push_front(new sll_node_t<pair_double_t>(aux_pair));
      aux_ptr_sum = sllpolsum.get_head();
    }
    aux_ptr = aux_ptr->get_next();
  }
} else { // Si el puntero de la segunda lista no es null pero el primero si,
         // metemos todos los valores sobrantes de la segunda lista en lista suma.
    while(aux_ptr2 != nullptr) {
    pair_double_t aux_pair(aux_ptr2->get_data().get_val(), aux_ptr2->get_data().get_inx());
    if(!sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps) {
      sllpolsum.insert_after(aux_ptr_sum, new sll_node_t<pair_double_t>(aux_pair));
      aux_ptr_sum = aux_ptr_sum->get_next();
    }
    if(sllpolsum.empty() && fabs(aux_pair.get_val()) >= eps){
      sllpolsum.push_front(new sll_node_t<pair_double_t>(aux_pair));
      aux_ptr_sum = sllpolsum.get_head();
    }
    aux_ptr2 = aux_ptr2->get_next();
    }
  }
}

// MODIFICACION
SllPolynomial SllPolynomial::Modify(SllPolynomial sp1) {
  SllPolynomial sp2;
  sll_node_t<pair_double_t>* aux_ptr = sp1.get_head()->get_next();
  pair_double_t aux(aux_ptr->get_data().get_val(), aux_ptr->get_data().get_inx());
  sp2.push_front(new sll_node_t<pair_double_t>(aux));
  sll_node_t<pair_double_t>* aux_ptr2 = sp2.get_head();
  aux_ptr = aux_ptr->get_next();

  while(aux_ptr != nullptr) {
    if(aux_ptr->get_next() == nullptr) {
      aux_ptr == nullptr;
    } else {
      pair_double_t aux2(aux_ptr->get_data().get_val(), aux_ptr->get_data().get_inx());
      sp2.insert_after(aux_ptr2, new sll_node_t<pair_double_t>(aux2));
    }
    aux_ptr = aux_ptr->get_next();
    aux_ptr2 = aux_ptr2->get_next();
  }

 return sp2;
}

#endif  // SLLPOLYNOMIAL_H_
