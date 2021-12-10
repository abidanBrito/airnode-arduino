// -*- mode: c++ -*-

// Nombre fichero: Publicador.h
// Fecha: 17/10/2021
// Autor: Jorge Grau Giannakakis
// Descripción: Controla las publicaciones

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
// --------------------------------------------------------------
class Publicador {

  // ............................................................
  // ............................................................
private:

  uint8_t beaconUUID1[16] = { 
	'-', 'E', 'P', 'S', 'G', '-', 'G', 'T', 
	'I', 'C', 'O', 'Y', 'C', 'O', '2', '-' 
	};
  uint8_t beaconUUID2[16] = { 
  'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
  'O', '3', 'Y', 'T', 'E', 'M', 'P', '-'
  };

  // ............................................................
  // ............................................................
public:
  EmisoraBLE laEmisora {
	"Jorge Grau Giannakakis, GTI-3A", //  nombre emisora
	  0x004c, // fabricanteID (Apple)
	  4 // txPower
	  };
  
  const int RSSI = -53; // por poner algo, de momento no lo uso

  // ............................................................
  // ............................................................
public:

  // ............................................................
  // ............................................................
  enum MedicionesID  {
	CO2 = 11,
	TEMPERATURA = 12,
	RUIDO = 13
  };

  // ............................................................
  // ............................................................
  Publicador( ) {
	// ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
	// Pondremos un método para llamarlo desde el setup() más tarde
  } // ()

  // ............................................................
  // -> EncenderEmisora ->
  // ............................................................
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } // ()

  // ............................................................
  // valorCO2: N, contador: N, tiempoEspera: N -> publicarCO2 ->
  // ............................................................
  void publicarCO2( int16_t valorCO2, uint8_t contador,
					long tiempoEspera ) {

	// 1. empezamos anuncio
	uint16_t major = 2;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID1, 
											major,
											valorCO2, // minor
											(*this).RSSI // rssi
									);

	// 2. esperamos el tiempo que nos digan
	esperar( tiempoEspera );

	// 3. paramos anuncio
	(*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  // valorTemperatura: N, contador: N, tiempoEspera: N-> publicarTemperatura ->
  // ............................................................
  void publicarTemperatura( int16_t valorTemperatura,
							uint8_t contador, long tiempoEspera ) {
  Serial.print(valorTemperatura + "Temperatura");
	uint16_t major = 1;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID1, 
											major,
											valorTemperatura, // minor
											(*this).RSSI // rssi
									);
	esperar( tiempoEspera );

	(*this).laEmisora.detenerAnuncio();
  } // ()
  
  // ............................................................
  // Esta funcion envia datos al dispositivo android
  // valorCO: N, valorCO2: N, tiempoEspera: N-> publicarCOYCO2 ->
  // @param {N} valorCO Valor random del CO
  // @param {N} valorCO2 Valor random de la CO2 
  // @param {N} tiempoEspera Tiempo que detiene el envio de datos  
  // ............................................................

void publicarCOYCO2( int16_t valorCO,
      int16_t valorCO2, long tiempoEspera ) {
        
  // Definimos el major
  uint16_t major = valorCO;
  
  // Definimos el minor
  uint16_t minor = valorCO2;
  
  (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID1, 
                      major,
                      minor, // minor
                      (*this).RSSI // rssi
                  );
  esperar( tiempoEspera );

  (*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  // Esta funcion envia datos al dispositivo android
  // valorO3: N,valorTemperatura: N, tiempoEspera: N-> publicarO3YTemperatura ->
  // @param {N} valorO3 Valor random del O3
  // @param {N} valorTemperatura Valor random de la temperatura 
  // @param {N} tiempoEspera Tiempo que detiene el envio de datos  
  // ............................................................
  
void publicarO3YTemperatura( int16_t valorO3,
  
  int16_t valorTemperatura, long tiempoEspera ) {
        
  // Definimos el major
  uint16_t major = valorO3;
  
  // Definimos el minor
  uint16_t minor = valorTemperatura;
  
  (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID2, 
                      major,
                      minor, // minor
                      (*this).RSSI // rssi
                  );
  esperar( tiempoEspera );

  (*this).laEmisora.detenerAnuncio();
  } // ()
  
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
