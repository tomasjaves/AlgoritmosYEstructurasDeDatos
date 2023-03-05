// AUTOR: Tomás Javes Tommasone
// FECHA: 
// EMAIL: alu0101515458@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 1
// COMENTARIOS: se indican entre [] las pautas de estilo aplicadas de
//              "C++ Programming Style Guidelines"
//              https://geosoft.no/development/cppstyle.html

// pauta de estilo [92]: comentarios multilínea usando solo "//"

#include "rational_t.hpp"

rational_t::rational_t(const int n, const int d)
{
  assert(d != 0);
  num_ = n, den_ = d;
}

// pauta de estilo [87]: 3 líneas de separación entre métodos

// pauta de estilo [83]: tipo retornado en línea anterior al método
int
rational_t::get_num() const
{
  return num_;
}



int
rational_t::get_den() const
{
  return den_;
}


  
void
rational_t::set_num(const int n)
{
  num_ = n;
}


  
void
rational_t::set_den(const int d)
{
  assert(d != 0);
  den_ = d;
}



double
rational_t::value() const
{ 
  return double(get_num()) / get_den();
}


// comparaciones
bool
rational_t::is_equal(const rational_t& r, const double precision) const
{
    if(abs(this->value()-r.value()) < precision) return true;
    else return false;
}



bool
rational_t::is_greater(const rational_t& r, const double precision) const
{
  if((this->value()-r.value()) > precision) return true;
  else return false;
}



bool
rational_t::is_less(const rational_t& r, const double precision) const
{
  if((r.value()-this->value()) > precision) return true;
  else return false;
}


// operaciones
rational_t
rational_t::add(const rational_t& r)
{
  rational_t resultado;
  if(this->get_den() == r.get_den()) {
    resultado.set_num(this->get_num() + r.get_num());
    resultado.set_den(r.get_den());
  } else {
    int denominador = this->get_den()*r.get_den();
    int aux1 = (denominador/this->get_den()) * this->get_num(), aux2 = (denominador/r.get_den()) * r.get_num();
    resultado.set_den(denominador);
    resultado.set_num(aux1 + aux2);
  }
  return resultado;
}


rational_t
rational_t::substract(const rational_t& r)
{
  rational_t resultado;
  if(this->get_den() == r.get_den()) {
    int numerador = this->get_num() - r.get_num();
    resultado.set_num(numerador);
    resultado.set_den(r.get_den());
  } else {
    int denominador = this->get_den()*r.get_den();
    int aux1 = (denominador/this->get_den()) * this->get_num(), aux2 = (denominador/r.get_den()) * r.get_num();
    resultado.set_den(denominador);
    resultado.set_num(aux1 - aux2);
  }
  return resultado;
}


rational_t
rational_t::multiply(const rational_t& r)
{
  rational_t resultado;
  resultado.set_num(this->get_num()*r.get_num());
  resultado.set_den(this->get_den()*r.get_den());
  return resultado;
}


rational_t
rational_t::divide(const rational_t& r)
{
  rational_t resultado;
  resultado.set_num(this->get_num()*r.get_den());
  resultado.set_den(this->get_den()*r.get_num());
  return resultado;
}

rational_t
rational_t::opposite(void) const
{
  rational_t resultado;
  resultado.set_num(-1*this->get_num());
  resultado.set_den(this->get_den());
  return resultado;
}


// E/S
void
rational_t::write(ostream& os) const
{
  os << get_num() << "/" << get_den() << "=" << value() << endl;
}



void 
rational_t::read(istream& is)
{
  cout << "Numerador? ";
  is >> num_;
  cout << "Denominador? ";
  is >> den_;
  assert(den_ != 0);
}
