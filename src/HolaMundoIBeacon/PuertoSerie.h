// -*- mode: c++ -*-

// Nombre fichero: PuertoSerie.h
// Fecha: 17/10/2021
// Autor: Jorge Grau Giannakakis
// Descripción: Clase PuertoSerie

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

// ----------------------------------------------------------
// ----------------------------------------------------------
class PuertoSerie  {

public:
  // .........................................................
  // baudios: N -> PuertoSerie ->
  // .........................................................
  PuertoSerie (long baudios) {
	Serial.begin( baudios );
  } // ()

  // .........................................................
  // -> esperarDisponible ->
  // .........................................................
  void esperarDisponible() {

	while ( !Serial ) {
	  delay(10);   
	}

  } // ()

  // .........................................................
  // mensaje: Texto -> escribir ->
  // .........................................................
  template<typename T>
  void escribir (T mensaje) {
	Serial.print( mensaje );
  } // ()
  
}; // class PuertoSerie

// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
