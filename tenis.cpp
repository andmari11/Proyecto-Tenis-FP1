//Calixto Sánchez-Fresnera Redondo y Andrés Marí Piqueras
#include <iostream>
#include <string> 
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
using namespace std;

const int LIM_INF_HAB = 1;
const int LIM_SUP_HAB = 3;
const int LIM_INF_VEL = 1;
const int LIM_SUP_VEL = 3;

const int ANCHO_PISTA = 7;
const int LARGO_PISTA = 2;

const int NUMERO_PUNTOS_SET = 3;

const int DIM_ARRAY_TENISTAS = 10;

const bool JUEGO_ALEATORIO = true;
const bool MODO_DEBUG = true;

typedef int tConteoGolpes[ANCHO_PISTA + 2];
typedef enum { nadie, tenista1, tenista2 } tTenista;
typedef enum { nada, quince, treinta, cuarenta, punto, ventaja } tPuntosJuego;

struct tDatosPartido {

    int posicion = 4;
    tPuntosJuego puntos = nada;
    int juegos = 0;
    int golpesGanadores = 0;

    tConteoGolpes golpes;
};

struct tDatosTenista {

    string nombre;
    int habilidad, velocidad, partidosGanados, partidosPerdidos;

    tDatosPartido datosPartido;
};

typedef tDatosTenista tArray[DIM_ARRAY_TENISTAS];

struct tListaTenistas {

    tArray tenistas;
    int contador = 0;
};

//muestra el menu y devuelve la opcion elegida por el usuario
int menu();

//se elige aleatoriamente quien saca al principio de un encuentro
int elegirSaque();

//devuelve la posicion en la que acaba el tenista que recibe
int correTenista(int posicion, int velocidad, int bola, string nombre);

//devuelve el destino final de la bola
int golpeoBola(int habilidad, int bola);

// el usuario introduce las iniciales de un jugadro y devuelve el numero de este si existe, o -1 si no existe
int buscarIniciales(const tListaTenistas& listaT, string ini);

// el usuario introduce la velocidad o habilidad del jugador
int introducirDato(string tipo, int max, int min);

//suma todos los golpes llevados a cabo
int golpeos_totales(const tConteoGolpes golpes);

//calcula el numeo de bolas que no han entrado en el campo
int golpeos_fallados(const tConteoGolpes golpes);

//chequea que no se haya elegido el tenista anteriormente y que el tenista existe
int disponibilidadTenista(tListaTenistas listaT, char numTenista, int pos1 = DIM_ARRAY_TENISTAS + 1, int pos2 = DIM_ARRAY_TENISTAS + 1, int pos3 = DIM_ARRAY_TENISTAS + 1);

//encuentra el jugador con el mayor numero de partidos ganados ignorando los tenistas indt
int compararPartidosGanados(tListaTenistas listaT, int indT1 = DIM_ARRAY_TENISTAS + 1, int indT2 = DIM_ARRAY_TENISTAS + 1, int indT3 = DIM_ARRAY_TENISTAS + 1);

//guarda la lista de tenistas del preograma en tenistas.txt
void guardar(const tListaTenistas& listaT);

//añade un tenista a la lista
void introducirTenista(tListaTenistas& listaT);

//pide las iniciales de un tenista y lo elimina
void eliminarTenista(tListaTenistas& listaT);

//selecciona a los 4 tenistas con mas partidos ganados
void seleccionarTop4(tListaTenistas& listaT);

//actualiza las estadisticas de los golpes
void actualizarGolpes(tConteoGolpes golpes, int& golpes_ganados, tTenista ganador, tTenista tenista, int pos_bola);

//muestra la posicion de la bola y los jugadores
void pintarPeloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, tTenista bola_jugador, int pos_bola);

//recibe la punctuacion y muestra al usuario el marcador
void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido& datos_t1, const tDatosPartido& datos_t2, tTenista servicio_para);

//muestra al usuario las estadisticas de los golpeos de un tenista
void mostrarEstadisticas(tDatosTenista tenista);

//en caso de empate, es necesario ganar dos puntos seguidos
void juice(tTenista ganador_punto, tPuntosJuego& puntosganador, tPuntosJuego& puntosperdedor);

//resetea la array elegida
void arrayReset(tConteoGolpes array);

//resetea las etadisticas del partido de cada tenista
void reseteoDatosPartido(tDatosTenista& tenista);

//el usuario elige 2 tenistas diferentes que juegan un partido
void partidoSimple(tListaTenistas& listaT);

//torneo entre 4 tenistas
void jugarTorneo(tListaTenistas& listaT, int indT1, int indT2, int indT3, int indT4);

//el usuario elige 4 tenistas y se juega un torneo entre los 4 tenistas diferentes elegidos por el usuario
void seleccionar4(tListaTenistas& listaT);

//muestra al usuario todas las iniciales de los tenistas
void mostrarIniciales(const tListaTenistas& listaT);

//el largo de la pista "| | | |"
void mostrarPistaVacia();

//zona donde podria estar la bola "| | |o| | |"
void mostrarPistaBola(int post, int pos_bola, tTenista bola_jugador, tTenista tenista);

//fin del campo "- - - - - - " 
void mostrarPistaFin();

//muestra posicion tenista
void mostrarPistaTenista(int pos, string nombre);

//muestra las estadisticas de cada tenista
void mostrarEstadisticas(const tListaTenistas& listaT);

//traslada los tenistas de tenistas.txt al programa
bool cargarLista(tListaTenistas& listaT);

//calcula el porcentaje de golpes en una pista respecto al total de golpes
double golpeos_porcentaje(double golpes, double golpesTotales);

//devuelve el equivalente de la puntuacion en cadena de texto
string puntosAstring(tPuntosJuego puntuacion);

//partido entre dos tenistas, actualiza los partidos ganados/perdidos de ambos y devuelve el ganador
tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2);

//se juega un set entre dos tenistas y devuelve el ganador
tTenista jugarSet(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para);

//devuelve el ganador del lanzamiento, tenista1, tenista2 o nadie 
tTenista lance(tTenista bola_para, tDatosTenista& tenista_golpea, tDatosTenista& tenista_recibe, int& pos_bola);

//actualiza los cambios de puntuacion y devuelve el ganador del encuentro
tTenista actualizarMarcador(tTenista ganador_punto, tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista& servicio_para);

//se juega un juego entre dos tenistas y devuelve el ganador
tTenista jugarJuego(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para);

//se juega un punto entre dos tenistas y devuelve el ganador
tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para);

int main() {

    tListaTenistas listaT;

    if (MODO_DEBUG == false) {

        srand(time(NULL));
    }
    else {

        srand(0);
    }

    //en caso de que la lista no se haya cargado correctamente no sera posible comenzar el simulador
    bool exit = (cargarLista(listaT) ? false : true);

    while (!exit) {

        switch (menu()) {

        case 1: mostrarEstadisticas(listaT);
            break;
        case 2: introducirTenista(listaT);
            break;
        case 3: eliminarTenista(listaT);
            break;
        case 4: partidoSimple(listaT);
            break;
        case 5: seleccionar4(listaT);
            break;
        case 6: seleccionarTop4(listaT);
            break;
        default: exit = true;
        }
    }

    return 0;
}

//muestra el menu y devuelve la opcion elegida por el usuario
int menu() {
    int opcion;

    cout << endl;
    cout << "o----------------------------------------------o" << endl;
    cout << "| Bienvenido al simulador de partidos de tenis |" << endl;
    cout << "o----------------------------------------------o" << endl << endl;

    cout << "<1> Ver datos tenistas" << endl;
    cout << "<2> Nuevo tenista" << endl;
    cout << "<3> Eliminar tenista" << endl;
    cout << "<4> Jugar partido" << endl;
    cout << "<5> Torneo semifinal/final" << endl;
    cout << "<6> Torneo top 4" << endl;
    cout << "<0> Salir" << endl << endl;

    cout << "Opcion: ";
    cin >> opcion;

    //el usuario ha introducido un numero no valido
    while (opcion < 0 or opcion > 6) {

        cout << endl << "ERROR: opcion no valida" << endl;
        cout << "Opcion: ";
        cin >> opcion;
    }

    return opcion;
}

//el usuario elige 4 tenistas y se juega un torneo entre los 4 tenistas diferentes elegidos por el usuario
void seleccionar4(tListaTenistas& listaT) {
    int pos1, pos2, pos3, pos4;
    string nombre;

    pos1 = disponibilidadTenista(listaT, '1');
    pos2 = disponibilidadTenista(listaT, '2', pos1);
    pos3 = disponibilidadTenista(listaT, '3', pos1, pos2);
    pos4 = disponibilidadTenista(listaT, '4', pos1, pos2, pos3);

    jugarTorneo(listaT, pos1, pos2, pos3, pos4);
}

//chequea que no se haya elegido el tenista anteriormente y que el tenista existe
int disponibilidadTenista(tListaTenistas listaT, char numTenista, int pos1, int pos2, int pos3) {
    string nombre;
    int pos;

    mostrarIniciales(listaT);
    cout << "Introduce las inciales del tenista " << numTenista << ": ";
    cin >> nombre;
    pos = buscarIniciales(listaT, nombre);

    //los valores predeterminados de pos1, pos2, pos3 son dim_array_tenistas +1,  por lo que no interferiran a no ser que se les asigne un valor menor
    while (pos < 0 or nombre == listaT.tenistas[pos1].nombre or nombre == listaT.tenistas[pos2].nombre or nombre == listaT.tenistas[pos3].nombre) {

        //el usuario ha introducido las iniciales de un tenista que no existe
        if (pos < 0) {

            cout << endl << "Error: no existe el tenista que busca" << endl;
        }

        //ya se ha elegido el tenista introducido
        if (nombre == listaT.tenistas[pos1].nombre or nombre == listaT.tenistas[pos2].nombre or nombre == listaT.tenistas[pos3].nombre) {

            cout << endl << "Error: tenista repetido" << endl;
        }

        cout << "Introduce las inciales del tenista " << numTenista << ": ";
        cin >> nombre;
        pos = buscarIniciales(listaT, nombre);
    }

    return pos;

}

//torneo entre 4 tenistas
void jugarTorneo(tListaTenistas& listaT, int indT1, int indT2, int indT3, int indT4) {

    int ganador1, ganador2, ganador3;

    cout << endl << "Primera semifinal: " << listaT.tenistas[indT1].nombre << " vs " << listaT.tenistas[indT4].nombre << endl;
    cout << "Segunda semifinal: " << listaT.tenistas[indT2].nombre << " vs " << listaT.tenistas[indT3].nombre << endl;

    if (jugarPartido(listaT.tenistas[indT1], listaT.tenistas[indT4]) == tTenista(1)) {

        //gana la semifinal indt1
        ganador1 = indT1;
    }
    else {

        //gana la semifinal indt2
        ganador1 = indT4;
    }

    if (jugarPartido(listaT.tenistas[indT2], listaT.tenistas[indT3]) == tTenista(1)) {

        //gana la semifinal indt3
        ganador2 = indT2;
    }
    else {

        //gana la semifinal indt4
        ganador2 = indT3;
    }

    cout << endl << "Final: " << listaT.tenistas[ganador1].nombre << " vs " << listaT.tenistas[ganador2].nombre;

    //sejuega la final entre los ganadores de las semifinales
    if (jugarPartido(listaT.tenistas[ganador1], listaT.tenistas[ganador2]) == tTenista(1)) {

        ganador3 = ganador1;
    }
    else {

        ganador3 = ganador2;
    }

    //se guardan los cambios en el archivo txt
    guardar(listaT);
    cout << endl << "GANADOR DEL TORNEO!!: " << listaT.tenistas[ganador3].nombre << endl;
}

//el usuario elige 2 tenistas diferentes que juegan un partido
void partidoSimple(tListaTenistas& listaT) {

    string nombre;
    int pos1, pos2;

    pos1 = disponibilidadTenista(listaT, '1');
    pos2 = disponibilidadTenista(listaT, '2', pos1);

    //se juega el partido entre los dos tenistas
    jugarPartido(listaT.tenistas[pos1], listaT.tenistas[pos2]);

    //se guardan los cambios en el archivo txt
    guardar(listaT);
}

//partido entre dos tenistas, actualiza los partidos ganados/perdidos de ambos y devuelve el ganador
tTenista jugarPartido(tDatosTenista& tenista1, tDatosTenista& tenista2) {

    tTenista servicio_para = tTenista(elegirSaque());

    if (jugarSet(tenista1, tenista2, servicio_para) == tTenista(1)) {

        //ha ganado el tenista 1
        tenista1.partidosGanados++;
        tenista2.partidosPerdidos++;

        return tTenista(1);
    }
    else {

        //ha ganado el tenista 2
        tenista2.partidosGanados++;
        tenista1.partidosPerdidos++;

        return tTenista(2);
    }

    return nadie;
}

//se juega un set entre dos tenistas y devuelve el ganador
tTenista jugarSet(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para) {

    bool finPartido = false;

    //resetea las etadisticas
    reseteoDatosPartido(tenista1);
    reseteoDatosPartido(tenista2);

    //se ejecuta hasta que haya un ganador	
    while (finPartido == false) {

        jugarJuego(tenista1, tenista2, servicio_para);

        //cada juego saca un jugador diferente
        if (servicio_para == tTenista(1)) {

            servicio_para = tTenista(2);
        }
        else {

            servicio_para = tTenista(1);
        }

        //gana el que llegue antes a tres puntos y es necesario ganar con dos puntos de diferencia
        if (tenista1.datosPartido.juegos >= NUMERO_PUNTOS_SET and tenista1.datosPartido.juegos - tenista2.datosPartido.juegos > 1) {

            finPartido = true;
            cout << "GANADOR!!: " << tenista1.nombre;
            return tTenista(1);
        }
        else if (tenista2.datosPartido.juegos >= NUMERO_PUNTOS_SET and tenista2.datosPartido.juegos - tenista1.datosPartido.juegos > 1) {

            finPartido = true;
            cout << "GANADOR!!: " << tenista2.nombre;
            return tTenista(2);
        }

    }
    return nadie;
}

//se juega un juego entre dos tenistas y devuelve el ganador
tTenista jugarJuego(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para) {

    tTenista ganador_punto = jugarPunto(tenista1, tenista2, servicio_para);
    tPuntosJuego puntos1 = nada, puntos2 = nada;


    //jugar hasta que haya un ganador
    while (actualizarMarcador(ganador_punto, tenista1, tenista2, servicio_para) == nadie) {

        //muestra la puntuacion
        pintarMarcador(tenista1.nombre, tenista2.nombre, tenista1.datosPartido, tenista2.datosPartido, servicio_para);

        //devuelve el ganador del punto
        ganador_punto = jugarPunto(tenista1, tenista2, servicio_para);

    }

    //muestra las estadisticas 
    mostrarEstadisticas(tenista1);
    mostrarEstadisticas(tenista2);

    //se cambia al que saca despues de cada punto
    if (servicio_para == tTenista(1)) {

        //antes sacaba el tenista1 ahora el tenista2
        servicio_para = tTenista(2);
    }
    else {

        //antes sacaba el tenista2 ahora el tenista1
        servicio_para = tTenista(1);
    }

    return ganador_punto;

}

//se juega un punto entre dos tenistas y devuelve el ganador
tTenista jugarPunto(tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista servicio_para) {

    tTenista ganador = nadie;
    int pos_bola = 4;

    tenista1.datosPartido.posicion = 4;
    tenista2.datosPartido.posicion = 4;

    pintarPeloteo(tenista1.nombre, tenista2.nombre, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, servicio_para, pos_bola);

    //se juega hasta que haya un ganador
    while (ganador == nadie) {

        if (servicio_para == tTenista(1)) {

            ganador = tTenista(lance(servicio_para, tenista1, tenista2, pos_bola));
            servicio_para = tTenista(2);
            actualizarGolpes(tenista1.datosPartido.golpes, tenista1.datosPartido.golpesGanadores, ganador, tTenista(1), pos_bola);

        }

        else if (servicio_para == tTenista(2)) {

            ganador = tTenista(lance(servicio_para, tenista2, tenista1, pos_bola));
            servicio_para = tTenista(1);
            actualizarGolpes(tenista2.datosPartido.golpes, tenista2.datosPartido.golpesGanadores, ganador, tTenista(2), pos_bola);

        }

        pintarPeloteo(tenista1.nombre, tenista2.nombre, tenista1.datosPartido.posicion, tenista2.datosPartido.posicion, servicio_para, pos_bola);

    }

    //devuelve el ganador
    return tTenista(ganador);

}

//en caso de empate, es necesario ganar dos puntos seguidos
void juice(tTenista ganador_punto, tPuntosJuego& puntosganador, tPuntosJuego& puntosperdedor) {

    if (tPuntosJuego(puntosganador) == cuarenta and tPuntosJuego(puntosperdedor) == cuarenta) {

        //consigue la ventaja el ganador del punto
        puntosganador = ventaja;
    }

    else if (tPuntosJuego(puntosganador) == cuarenta and tPuntosJuego(puntosperdedor) == ventaja) {

        //consigue empatar el ganador del punto
        puntosperdedor = cuarenta;
    }

    else if (tPuntosJuego(puntosganador) == ventaja and tPuntosJuego(puntosperdedor) == cuarenta) {

        //consigue ganar el juego el ganador del punto
        puntosganador = punto;

    }

}

//devuelve el destino final de la bola
int golpeoBola(int habilidad, int bola) {
    int destino;

    if (JUEGO_ALEATORIO == false) {

        cout << "Elija el destino de la bola: "; //juego controlado por usuario
        cin >> destino;
    }

    else if (JUEGO_ALEATORIO) { //juego aleatorio

        destino = rand() % ANCHO_PISTA + 1;
        cout << endl;
        system("PAUSE");
        cout << endl;

    }

    int distancia = abs(bola - destino);

    if (distancia <= habilidad) { //la bola llega 100% a su destino debido a la habilidad

        bola = destino;

        if (MODO_DEBUG) {

            cout << "No se la juega mandando la bola a " << destino << endl;
        }
    }

    else {

        double probabilidad = 100.00 - 100.00 * (distancia - habilidad) / (ANCHO_PISTA - 1 - LIM_INF_HAB); //la bola tiene probabilidades de desviarse a la izquierda o a la derecha

        if (MODO_DEBUG) {

            cout << "Opta por una bola arriesgada dirigida a " << destino << endl;
        }


        int probabilidad2 = rand() % 100;

        if (MODO_DEBUG) {

            cout << "(Probabilidades de exito: " << probabilidad << "|| Resultado: " << probabilidad2 << ")" << endl;
        }

        if (probabilidad2 < probabilidad) { //la bola llega al destino deseado sin desviar

            if (MODO_DEBUG) {

                cout << "Que no se desvía " << endl;
            }

            bola = destino;
        }

        else { // la bola se desvia

            if (probabilidad2 % 2 == 0) { // la bola se desvía a la derecha

                bola = destino + 1;
            }

            else {

                bola = destino - 1; // la bola se desvía a la izquierda
            }

            if (MODO_DEBUG) {

                cout << "Desgraciadamente se le desvía a " << bola << endl;
            }
        }
    }


    return bola;
}

//devuelve la posicion en la que acaba el tenista que recibe
int correTenista(int posicion, int velocidad, int bola, string nombre) {
    int distancia;

    distancia = abs(posicion - bola);

    if (distancia <= velocidad) {   //jugador llega la pelota

        posicion = bola;

        if (MODO_DEBUG) {

            cout << nombre << " llega sin problema alguno" << endl;
        }


        return posicion;
    }
    else if (distancia > velocidad) { //jugador no llega

        if (posicion < bola) {

            posicion = posicion + velocidad;  //la bola se le queda a la derecha

            if (MODO_DEBUG) {

                cout << nombre << " no llega, quedándose en la casilla  " << posicion << " y la bola en " << bola << "." << endl;
            }

            return posicion;
        }
        else if (posicion > bola) {

            posicion = posicion - velocidad; // la bola se queda a la izquierda

            if (MODO_DEBUG) {

                cout << nombre << " no llega, quedándose en la casilla  " << posicion << " y la bola en " << bola << "." << endl;
            }

            return posicion;
        }

    }
    return posicion;
}

//devuelve el ganador del lanzamiento, tenista1, tenista2 o nadie 
tTenista lance(tTenista bola_para, tDatosTenista& tenista_golpea, tDatosTenista& tenista_recibe, int& pos_bola) {

    pos_bola = golpeoBola(tenista_golpea.habilidad, pos_bola);

    //la bola sale fuera
    if (pos_bola < 1 or pos_bola > ANCHO_PISTA) {

        //golepaba el tenista1 por lo que gana el tenista 2
        if (bola_para == tenista1) {

            return tenista2;
        }
        //golpeaba el tenista2 por lo que gana el tenista 1
        else {

            return tenista1;
        }
    }

    //actualiza la poscion del tenista que recibe
    tenista_recibe.datosPartido.posicion = correTenista(tenista_recibe.datosPartido.posicion, tenista_recibe.velocidad, pos_bola, tenista_recibe.nombre);

    //el receptor llega
    if (tenista_recibe.datosPartido.posicion == pos_bola) {

        return nadie;
    }
    //el receptor no llega
    else {

        return bola_para;
    }

}

//devuelve el equivalente de la puntuacion en cadena de texto
string puntosAstring(tPuntosJuego punt) {

    if (tPuntosJuego(punt) == nada) {

        return "00";
    }
    else if (tPuntosJuego(punt) == quince) {

        return "15";
    }
    else if (tPuntosJuego(punt) == treinta) {

        return "30";
    }
    else if (tPuntosJuego(punt) == cuarenta) {

        return "40";
    }
    else if (tPuntosJuego(punt) == ventaja) {

        return "[ad]";
    }
    else if (tPuntosJuego(punt) == punto) {

        return "punto";
    }
    return "00";

}

//recibe la punctuacion y muestra al usuario el marcador
void pintarMarcador(string iniciales1, string iniciales2, const tDatosPartido& datos_t1, const tDatosPartido& datos_t2, tTenista servicio_para) {

    cout << endl;
    string saque = (servicio_para == tenista1) ? " *" : " ";
    cout << setw(5) << iniciales1 << setw(3) << datos_t1.juegos << " : " << puntosAstring(datos_t1.puntos) << saque << endl;

    saque = (servicio_para == tenista2) ? " *" : " ";
    cout << setw(5) << iniciales2 << setw(3) << datos_t2.juegos << " : " << puntosAstring(datos_t2.puntos) << saque << endl;

}

//actualiza los cambios de puntuacion y devuelve el ganador del encuentro
tTenista actualizarMarcador(tTenista ganador_punto, tDatosTenista& tenista1, tDatosTenista& tenista2, tTenista& servicio_para) {

    bool empate = false;

    //en caso de 40-40 es necesario que se gane 2 puntos seguidos
    if (tPuntosJuego(tenista1.datosPartido.puntos) >= cuarenta and tPuntosJuego(tenista2.datosPartido.puntos) >= cuarenta) {

        empate = true;
    }

    //no hay empate por lo que se juega hasta 40
    if (!empate) {

        //tenista1 gana un punto
        if ((ganador_punto) == tTenista(1)) {

            int puntuacion = tenista1.datosPartido.puntos;
            puntuacion++;
            tenista1.datosPartido.puntos = tPuntosJuego(puntuacion);
        }

        //tenista2 gana un punto
        else if ((ganador_punto) == tTenista(2)) {

            int puntuacion = tenista2.datosPartido.puntos;
            puntuacion++;
            tenista2.datosPartido.puntos = tPuntosJuego(puntuacion);
        }

    }

    //hay empate
    else {

        if ((ganador_punto) == 1) {

            juice(ganador_punto, tenista1.datosPartido.puntos, tenista2.datosPartido.puntos);
        }
        else if (ganador_punto == 2) {

            juice(ganador_punto, tenista2.datosPartido.puntos, tenista1.datosPartido.puntos);
        }

    }

    //el jugador1 llega a ganar un juego
    if (tPuntosJuego(tenista1.datosPartido.puntos) == punto) {

        tenista2.datosPartido.puntos = nada;
        tenista1.datosPartido.puntos = nada;
        tenista1.datosPartido.juegos++;
        return tTenista(1);
    }

    //el jugador2 llega a ganar un juego
    else if (tPuntosJuego(tenista2.datosPartido.puntos) == punto) {

        tenista1.datosPartido.puntos = nada;
        tenista2.datosPartido.puntos = nada;
        tenista2.datosPartido.juegos++;
        return tTenista(2);
    }

    return nadie;

}

//actualiza las estadisticas de los golpes
void actualizarGolpes(tConteoGolpes golpes, int& golpes_ganados, tTenista ganador, tTenista tenista, int pos_bola) {

    //golpes en cada calle
    for (int i = 0; i < ANCHO_PISTA + 2; i++) {

        if (pos_bola == i) {

            golpes[i]++;

        }
    }

    //golpe ganador?
    if (tenista == ganador) {

        golpes_ganados++;
    }

}

//resetea la array elegida
void arrayReset(tConteoGolpes array) {

    for (int i = 0; i < ANCHO_PISTA + 2; i++) {

        array[i] = 0;
    }
}

//calcula el porcentaje de golpes en una pista respecto al total de golpes
double golpeos_porcentaje(double golpes, double golpesTotales) {

    double porcentaje = 0;

    porcentaje = 100 * (golpes / golpesTotales);


    return porcentaje;
}

//suma todos los golpes llevados a cabo
int golpeos_totales(const tConteoGolpes golpes) {

    int total = 0;

    for (int i = 0; i < ANCHO_PISTA + 2; i++) {

        total = total + golpes[i];
    }

    return total;
}

//muestra al usuario las estadisticas de los golpeos de un tenista
void mostrarEstadisticas(tDatosTenista tenista) {

    int total = golpeos_totales(tenista.datosPartido.golpes);

    cout << "Estadisticas de " << tenista.nombre << endl;
    cout << setw(5) << "Golpes totales: " << total << endl;
    cout << setw(5) << "Golpes ganadores: " << tenista.datosPartido.golpesGanadores << endl;
    cout << setw(5) << "Errores no forzados: " << golpeos_fallados(tenista.datosPartido.golpes) << endl;
    cout << setw(5) << "Distribución de los golpes en la pista " << endl;
    cout << setw(6) << "Calle ";

    //numero de pistas
    for (int i = 0; i < ANCHO_PISTA + 2; i++) {

        cout << setw(6) << i;

    }
    cout << endl;

    //porcentaje de cada pista
    cout << setw(6) << "%";
    for (int i = 0; i < ANCHO_PISTA + 2; i++) {

        cout << setw(6) << fixed << setprecision(1) << golpeos_porcentaje(tenista.datosPartido.golpes[i], total);

    }
    cout << endl << endl;

}

//muestra la posicion de la bola y los jugadores
void pintarPeloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, tTenista bola_jugador, int pos_bola) {

    mostrarPistaTenista(pos_t1, nombre1);
    mostrarPistaFin();
    mostrarPistaBola(pos_t1, pos_bola, bola_jugador, tenista1);
    mostrarPistaVacia();

    //numero de pista "-1-2-3"
    cout << "-";
    for (int i = 1; i <= (ANCHO_PISTA); i++) {

        cout << "-" << i;
    }
    cout << "--" << endl;

    mostrarPistaVacia();
    mostrarPistaBola(pos_t2, pos_bola, bola_jugador, tenista2);
    mostrarPistaFin();
    mostrarPistaTenista(pos_t2, nombre2);
}

//el largo de la pista "| | | |"
void mostrarPistaVacia() {

    for (int e = 1; e <= (LARGO_PISTA - 1); e++) {
        cout << " ";
        for (int i = 1; i <= (ANCHO_PISTA); i++) {

            cout << "| ";
        }
        cout << "|" << endl;

    }
}

//zona donde podria estar la bola "| | |o| | |"
void mostrarPistaBola(int post, int pos_bola, tTenista bola_jugador, tTenista tenista) {

    if (tTenista(bola_jugador) == tenista) {
        cout << " ";
        for (int i = 1; i <= (ANCHO_PISTA); i++) {

            if (i == pos_bola) {

                cout << "|o";
            }

            else {

                cout << "| ";
            }
        }
        cout << "|" << endl;
    }
    //no es el turno de este tenista, la bola esta al otro lado
    else {

        cout << " ";
        for (int i = 1; i <= (ANCHO_PISTA); i++) {

            cout << "| ";
        }
        cout << "|" << endl;
    }
}

//fin del campo "- - - - - - " 
void mostrarPistaFin() {

    //fin del campo "- - - - - - " 
    cout << " ";
    for (int i = 1; i <= (ANCHO_PISTA); i++) {

        cout << " -";
    }
    cout << endl;

}

//muestra posicion tenista
void mostrarPistaTenista(int pos, string nombre) {

    //coloca al tenista
    for (int i = 1; i <= (ANCHO_PISTA); i++) {

        if (i == pos) {

            cout << " " << nombre;
        }

        else {

            cout << "  ";
        }
    }
    cout << endl;
}

//calcula el numeo de bolas que no han entrado en el campo
int golpeos_fallados(const tConteoGolpes golpes) {

    int golpesValidos = 0;
    int total = golpeos_totales(golpes);

    for (int i = 1; i < ANCHO_PISTA + 1; i++) {

        golpesValidos = golpesValidos + golpes[i];
    }

    return (total - golpesValidos);

}

//selecciona a los 4 tenistas con mas partidos ganados
void seleccionarTop4(tListaTenistas& listaT) {

    int indT1, indT2, indT3, indT4;

    indT1 = compararPartidosGanados(listaT);
    indT2 = compararPartidosGanados(listaT, indT1);
    indT3 = compararPartidosGanados(listaT, indT1, indT2);
    indT4 = compararPartidosGanados(listaT, indT1, indT2, indT3);

    jugarTorneo(listaT, indT1, indT2, indT3, indT4);

}

//encuentra el jugador con el mayor numero de partidos ganados ignorando los tenistas indt
int compararPartidosGanados(tListaTenistas listaT, int indT1, int indT2, int indT3) {

    int indt, ganados = -1;

    for (int i = 0; i < listaT.contador; i++) {

        //se saltan los tenistas indt, que tienen como valor predeterminado dim_array_tenistas + 1
        while (i == indT1 or i == indT2 or i == indT3) {

            i++;
        }
        //el tenista tiene el mayor valor hasta ahora
        if (listaT.tenistas[i].partidosGanados > ganados) {

            indt = i;
            ganados = listaT.tenistas[indt].partidosGanados;

        }
    }
    return indt;
}

//se elige aleatoriamente quien saca al principio de un encuentro
int elegirSaque() {
    int probabilidad;

    probabilidad = rand() % 2;

    if (probabilidad == 0) {
        cout << endl << "Empieza sacando el jugador 1" << endl;

        return 1;
    }
    else {
        cout << endl << "Empieza sacando el jugador 2" << endl;

        return 2;
    }
}

// elimina un tenista
void eliminarTenista(tListaTenistas& listaT) {

    string iniciales;
    mostrarIniciales(listaT);
    cout << "Introduce las iniciales a eliminar: ";
    cin >> iniciales;

    int pos = buscarIniciales(listaT, iniciales);

    //en caso de que no existan las iniciales introducidas
    while (pos < 0) {

        cout << "ERROR: no se encontro el nombre";
        cout << endl << "Introduce las iniciales a eliminar: ";
        cin >> iniciales;

        pos = buscarIniciales(listaT, iniciales);
    }

    //en caso de que el tenista no sea el ultimo de la lista
    if (pos != listaT.contador - 1) {

        //se sustituye por el siguiente tenista
        for (int i = pos; i < listaT.contador; i++) {

            listaT.tenistas[i].nombre = listaT.tenistas[i + 1].nombre;
            listaT.tenistas[i].habilidad = listaT.tenistas[i + 1].habilidad;
            listaT.tenistas[i].velocidad = listaT.tenistas[i + 1].velocidad;
            listaT.tenistas[i].partidosGanados = listaT.tenistas[i + 1].partidosGanados;
            listaT.tenistas[i].partidosPerdidos = listaT.tenistas[i + 1].partidosPerdidos;
        }
    }

    listaT.contador--;
    guardar(listaT);
}

// el usuario introduce las iniciales de un jugadro y devuelve el numero de este si existe, o -1 si no existe
int buscarIniciales(const tListaTenistas& listaT, string ini) {

    int i;
    for (i = 0; ini != listaT.tenistas[i].nombre and i < DIM_ARRAY_TENISTAS; i++) {}

    //se ha llegado al final de la lista sin encontrar el nombre, por lo que no existe nigun tenista con ese nombre
    if (i == DIM_ARRAY_TENISTAS) {

        return -1;
    }
    //se ha encontrado al tenista por lo que se envia su numero
    else {

        return i;
    }

}

// el usuario introduce la velocidad o habilidad del jugador
int introducirDato(string tipo, int max, int min) {
    int dato;

    cout << "Introduzca la " << tipo << ": ";
    cin >> dato;

    //el usuario no introduce un valor valido
    while (min > dato or max < dato) {

        cout << "Vuelve a introducir la " << tipo << " ,solo puede ser de " << LIM_INF_VEL << " a " << LIM_SUP_VEL << endl;
        cin >> dato;
    }

    return dato;
}

//traslada los tenistas de tenistas.txt al programa
bool cargarLista(tListaTenistas& listaT) {

    char aux;
    ifstream archivo;
    archivo.open("tenistas.txt");

    //no se encuentra el archivo
    if (!archivo.is_open()) {

        cout << "ERROR: no se ha encontrado el archivo tenistas.txt";
        return false;
    }
    //se carga cada uno de los tenistas
    else {

        for (int i = 0; i < DIM_ARRAY_TENISTAS and !archivo.eof(); i++) {

            archivo >> listaT.tenistas[i].nombre;

            //en caso de que el archivo de texto este vacio
            if (archivo.eof()) {

                return true;
            }

            archivo >> listaT.tenistas[i].habilidad;
            archivo >> listaT.tenistas[i].velocidad;
            archivo >> listaT.tenistas[i].partidosGanados;
            archivo >> listaT.tenistas[i].partidosPerdidos;
            archivo.get(aux);

            listaT.contador++;
        }

        archivo.close();
        return true;
    }
    return true;
}

//añade un tenista a la lista
void introducirTenista(tListaTenistas& listaT) {

    //se ha alcanzado el maximo de tenistas
    if (listaT.contador >= DIM_ARRAY_TENISTAS) {

        cout << "ERROR: Se ha alcanzado el numero maximo de tenistas (" << DIM_ARRAY_TENISTAS << ")" << endl;
    }
    else {

        int i = listaT.contador;
        string nombre;

        //pide el nombre al usuario
        cout << "Iniciales del tenista: ";
        cin >> nombre;

        int pos = buscarIniciales(listaT, nombre);


        //en caso de que ya exista un tenista con ese nombre
        while (pos >= 0) {

            cout << "ERROR: ya existe un tenista con ese nombre";
            cout << endl << "Introduce las iniciales a eliminar: ";
            cin >> nombre;

            pos = buscarIniciales(listaT, nombre);
        }

        listaT.tenistas[i].nombre = nombre;

        //se ejecuta hasta que el nombre sea valido
        while (listaT.tenistas[i].nombre.length() != 3) {

            cout << "Solo se pueden introducir tres caracteres " << endl;
            cout << "Introduzca de nuevo las niciales del tenista: ";
            cin >> listaT.tenistas[i].nombre;

        }

        listaT.tenistas[i].habilidad = introducirDato("habilidad", LIM_SUP_HAB, LIM_INF_HAB);
        listaT.tenistas[i].velocidad = introducirDato("velocidad", LIM_SUP_VEL, LIM_INF_VEL);
        listaT.tenistas[i].partidosGanados = 0;
        listaT.tenistas[i].partidosPerdidos = 0;
        listaT.contador++;

        cout << endl;

        guardar(listaT);
    }
}

//guarda la lista de tenistas del preograma en tenistas.txt
void guardar(const tListaTenistas& listaT) {

    ofstream archivo;
    archivo.open("tenistas.txt");

    //no se encuentra el archivo
    if (!archivo.is_open()) {

        cout << "ERROR: no se ha encontrado el archivo tenistas.txt";
    }

    //se guarda cada uno de los tenistas
    for (int i = 0; i < listaT.contador; i++) {

        if (i != 0) {

            archivo << endl;
        }

        archivo << listaT.tenistas[i].nombre;
        archivo << " ";
        archivo << listaT.tenistas[i].habilidad;
        archivo << " ";
        archivo << listaT.tenistas[i].velocidad;
        archivo << " ";
        archivo << listaT.tenistas[i].partidosGanados;
        archivo << " ";
        archivo << listaT.tenistas[i].partidosPerdidos;

    }

    archivo.close();
}

//muestra al usuario todas las iniciales de los tenistas
void mostrarIniciales(const tListaTenistas& listaT) {

    cout << "Iniciales de los tenistas:  ";

    for (int i = 0; i < listaT.contador; i++) {

        cout << listaT.tenistas[i].nombre;

        //si no es el ultimo tenista
        if (i != listaT.contador - 1) {

            cout << " - ";
        }
        //si es el ultimo tenista
        else {

            cout << endl;
        }
    }
}

void mostrarEstadisticas(const tListaTenistas& listaT) {

    cout << setw(2) << "INI" << setw(5) << "HAB" << setw(5) << "VEL" << setw(4) << "PG" << setw(4) << "PP" << endl;

    for (int i = 0; i < listaT.contador; i++){
        
        cout << setw(2) << listaT.tenistas[i].nombre << setw(5) << listaT.tenistas[i].habilidad << setw(5) << listaT.tenistas[i].velocidad << setw(4) << listaT.tenistas[i].partidosGanados << setw(4) << listaT.tenistas[i].partidosPerdidos << endl;
    }
}

//resetea las etadisticas del partido de cada tenista
void reseteoDatosPartido(tDatosTenista& tenista) {

    arrayReset(tenista.datosPartido.golpes);
    tenista.datosPartido.juegos = 0;
    tenista.datosPartido.puntos = nada;
    tenista.datosPartido.golpesGanadores = 0;
}