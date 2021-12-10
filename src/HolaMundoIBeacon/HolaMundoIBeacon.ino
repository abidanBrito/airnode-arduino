// -*-c++-*-

// Nombre fichero: HolaMundoBeacon
// Fecha: 17/10/2021
// Autor: Jorge Grau Giannakakis
// Descripción: El programa

// --------------------------------------------------------------
// --------------------------------------------------------------
#include <bluefruit.h>

#undef min 
#undef max 

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 115200 ); // 115200 o 9600 o ... 
};

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"


// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  Publicador elPublicador;

  Medidor elMedidor;

}; // namespace

// --------------------------------------------------------------
// -> inicializarPlaquita ->
// --------------------------------------------------------------
void inicializarPlaquita () {

  // de momento nada

} // ()

// --------------------------------------------------------------
// setup()
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.esperarDisponible();
  
  inicializarPlaquita();
 
  Globales::elPublicador.encenderEmisora();
  
  Globales::elMedidor.iniciarMedidor();

  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
// -> lucecitas ->
// --------------------------------------------------------------
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 1000 ); // 1000 encendido
  esperar ( 1000 ); //  100 apagado
} // ()

// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
};

// ..............................................................
// ..............................................................
void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );


  lucecitas();
/*
  // mido y publico
  int valorCO2 = elMedidor.medirCO2();

  elPuerto.escribir(valorCO2);
  
  elPublicador.publicarCO2( valorCO2,
							cont,
							1000 // intervalo de emisión
							);
              
  // mido y publico
  int valorTemperatura = elMedidor.medirTemperatura();
  
  elPublicador.publicarTemperatura( valorTemperatura, 
									cont,
									1000 // intervalo de emisión
									);
*/

int16_t valorCO = random(10 40);
int16_t valorCO2 = random(10, 30);
int16_t valorO3 = random(15, 70);
int16_t valorTemperatura = random(0, 15);

  elPuerto.escribir( "\n---- Valor CO " );
  elPuerto.escribir( valorCO );
  elPuerto.escribir( "\n" );
  elPuerto.escribir( "\n---- Valor CO2 " );
  elPuerto.escribir( valorCO2 );
  elPuerto.escribir( "\n" );
  elPuerto.escribir( "\n---- Valor O3 " );
  elPuerto.escribir( valorO3 );
  elPuerto.escribir( "\n" );
  elPuerto.escribir( "\n---- Valor Temperatura " );
  elPuerto.escribir( valorTemperatura );
  elPuerto.escribir( "\n" );
/*
int16_t valorCO = -20;
int16_t valorCO2 = 40;
int16_t valorO3 = 15;
int16_t valorTemperatura = 55;
*/
  elPublicador.publicarCOYCO2(valorCO, valorCO2, 1000);

  elPublicador.publicarO3YTemperatura(valorO3, valorTemperatura, 1000);

         
  // prueba para emitir un iBeacon y poner
  // en la carga (21 bytes = uuid 16 major 2 minor 2 txPower 1 )
  // lo que queramos (sin seguir dicho formato)
  /*
  char datos[21] = {
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H'
  };
  */
  // elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( &datos[0], 21 )
  //elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( "MolaMolaMolaMolaMolaM", 21 );

  esperar( 2000 );

  elPublicador.laEmisora.detenerAnuncio();
  
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
