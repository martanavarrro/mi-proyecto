/***********************************************************************************
 * Fichero valoraciones.cpp para la implementación de los métodos de la clase
 * Valoraciones para la gestión de la información correspondiente a una lista de 
 * valoraciones de alojamientos turísticos.
 *
 * Alumno/a: 
 * Fecha: 
 * *********************************************************************************/
#include "valoracion.hpp"
#include "valoraciones.hpp"
#include "palabras.hpp"
#include "utilidades.hpp"
#include <string>
#include <fstream>
#include <cassert>
#include <cctype>
#include <sstream>

using namespace std;

namespace bblProg2
{
    // --------------------- MÉTODOS PÚBLICOS IMPLEMENTADOS POR EL PROFESORADO (NO MODIFICAR)

    // Operador de asignación de la clase Valoraciones
    Valoraciones &Valoraciones::operator=(const Valoraciones &otro_objeto)
    {
        if (this != &otro_objeto)
        {
            borrarValoraciones(valoraciones);
            valoraciones = copiarValoraciones(otro_objeto.valoraciones);
            num_valoraciones = otro_objeto.num_valoraciones;
            pal_pos = otro_objeto.pal_pos;
            pal_neg = otro_objeto.pal_neg;
        }

        return *this;
    }

    // Operador de comparación de igualdad de Valoraciones
    // (SOLO NECESARIO PARA LAS PRUEBAS UNITARIAS.)
    // (IMPLEMENTADO POR EL PROFESORADO. NO MODIFICAR.)
    bool Valoraciones::operator==(const Valoraciones &otro_objeto) const
    {
        bool iguales = (num_valoraciones == otro_objeto.num_valoraciones &&
                        pal_pos == otro_objeto.pal_pos &&
                        pal_neg == otro_objeto.pal_neg);

        PtrValoracion ptr1 = valoraciones, ptr2 = otro_objeto.valoraciones;

        while (iguales && ptr1 != nullptr)
        {
            iguales = ptr1->valoracion == ptr2->valoracion;
            ptr1 = ptr1->sig;
            ptr2 = ptr2->sig;
        }

        return iguales;
    }

    // Función auxiliar
    // (SOLO NECESARIA PARA LAS PRUEBAS UNITARIAS.)
    // (IMPLEMENTADA POR EL PROFESORADO.)
    void Valoraciones::__consultar_elemento_pos(unsigned pos, bool val_pal, bool pos_neg, Valoracion &valoracion, std::string &palabra) const
    {
        assert((val_pal && pos < num_valoraciones) ||
               (!val_pal && pos_neg && pos < pal_pos.numPalabras()) ||
               (!val_pal && !pos_neg && pos < pal_neg.numPalabras()));

        if (val_pal) // Consulto valoración
        {
            PtrValoracion ptr = valoraciones;
            unsigned i = 0;
            while (i < pos)
            {
                ++i;
                ptr = ptr->sig;
            }
            valoracion = ptr->valoracion;
        }
        else // Consulto palabra
        {
            if (pos_neg) // Consulto palabra positiva
            {
                palabra = pal_pos[pos];
            }
            else // Consulto palabra negativa
            {
                palabra = pal_neg[pos];
            }
        }
    }
    // -----------------------------------------------------------------

    // IMPLEMENTACIÓN DE LOS MÉTODOS PÚBLICOS Y PRIVADOS



    //Constructor por defecto
    Valoraciones:: Valoraciones(): valoraciones{},num_valoraciones{},pal_pos{},pal_neg{}{}





    //Constructor de copia
    Valoraciones::Valoraciones(const Valoraciones &otro_objeto): pal_pos{otro_objeto.pal_pos}, pal_neg{otro_objeto.pal_neg}, 
          num_valoraciones{otro_objeto.num_valoraciones} {

        // Copiar la lista de valoraciones 
        PtrValoracion copia_lista = copiarValoraciones(otro_objeto.valoraciones);

        // Asignar la copia directamente a la lista privada
        valoraciones = copia_lista;}

   


//Destructor

Valoraciones::~Valoraciones() {
    // Liberar la memoria de la lista de valoraciones
    PtrValoracion ptr_actual = valoraciones;
    PtrValoracion ptr_siguiente = nullptr;

    while (ptr_actual != nullptr) {
        ptr_siguiente = ptr_actual->sig;  // Guardar el siguiente nodo
        delete ptr_actual;                // Eliminar el nodo actual
        ptr_actual = ptr_siguiente;       // Avanzar al siguiente nodo
    }}



//CARGAR PALABRAS POSITIVAS

        // Lee desde fichero la lista de palabras positivas
        // y la almacena en el objeto. Si el fichero ha podido abrirse
        // correctamente para lectura, devuelve OK a través de 'res'. Si no,
        // devuelve FIC_ERROR.
        // Parámetros:
        //  - nombre_fic (E): nombre del fichero de palabras positivas
        //  - res (S): resultado de la apertura del fichero para lectura

void Valoraciones::cargarPalabrasPositivas(const std::string &nombre_fic, Resultado &res) {
    pal_pos.leerPalabras(nombre_fic, res);}



//CARGAR PALABRAS NEGATIVAS

        // Lee desde fichero la lista de palabras negativas
        // y la almacena en el objeto. Si el fichero ha podido abrirse
        // correctamente para lectura, devuelve OK a través de 'res'. Si no,
        // devuelve FIC_ERROR.
        // Parámetros:
        //  - nombre_fic (E): nombre del fichero de palabras positivas
        //  - res (S): resultado de la apertura del fichero para lectura

void Valoraciones::cargarPalabrasNegativas(const std::string &nombre_fic, Resultado &res) {
    pal_neg.leerPalabras(nombre_fic, res);}

       
       


//CARGAR VALORACIONES

        // Lee valoraciones de un fichero de valoraciones y las incorpora
        // (añadiéndolas a las ya existentes) a la lista de valoraciones
        // actual.
        // Antes de insertar la valoración en la lista de valoraciones debe
        // analizarse y actualizarse el sentimiento (positivo, negativo o neutro)
        // del comentario que incluye.
        // La valoraciones deben insertarse en orden creciente de identificador
        // de valoración dentro de la lista de valoraciones.
        // Si el fichero puede abrirse correctamente para lectura, se leen las valoraciones,
        // se incorporan al objeto actual y se devuelve OK a través de 'res'. Si no,
        // se devuelve FIC_ERROR  a través de 'res'.
        // FORMATO DEL FICHERO:
        //  - El fichero debe comenzar con la siguiente cabecera (véase 'valoraciones.csv'):
        //      id_alojamiento,id_valoracion,fecha,id_revisor,nombre_revisor,comentario
        //  - Los datos deben separarse con comas
        //  - Si el nombre del revisor incluye comas, aparecerá en el fichero entre comillas dobles.
        //    Por ejemplo: "Smith, John"
        //  - Si el nombre del revisor NO incluye comas, no aparecerá en el fichero entre comillas dobles.
        //    Por ejemplo: John Smith
        //  - Si el comentario incluye comas, aparecerá en el fichero entre comillas dobles.
        //    Por ejemplo: "Este comentario, como puede verse, incluye comas"
        //  - Si el comentario no incluye comas, no aparecerá entre comillas dobles.
        //    Por ejemplo: Este comentario no necesita comillas porque no incluye comas
        // PARÁMETROS:
        //  - nombre_fic (E): nombre del fichero de valoraciones
        //  - res (S): resultado de la operación

void Valoraciones::cargarValoraciones(const std::string &nombre_fic, Resultado &res) {
    std::ifstream archivo(nombre_fic);
    if (!archivo) {
        res = FIC_ERROR;
        return;
    }

    std::string linea;
    std::getline(archivo, linea); // Leer y descartar la cabecera

    while (std::getline(archivo, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        size_t pos3 = linea.find(',', pos2 + 1);
        size_t pos4 = linea.find(',', pos3 + 1);
        size_t pos5 = linea.find(',', pos4 + 1);

        if (pos1 == std::string::npos || pos5 == std::string::npos) {
            continue; // Saltar líneas mal formateadas
        }

        unsigned id_alojamiento = std::stoi(linea.substr(0, pos1));
        unsigned id_valoracion = std::stoi(linea.substr(pos1 + 1, pos2 - pos1 - 1));
        std::string fecha = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        unsigned id_revisor = std::stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1));
        std::string nombre_revisor = linea.substr(pos4 + 1, pos5 - pos4 - 1);
        std::string comentario = linea.substr(pos5 + 1);

        // Limpiar comillas
        if (!nombre_revisor.empty() && nombre_revisor.front() == '"' && nombre_revisor.back() == '"') {
            nombre_revisor = nombre_revisor.substr(1, nombre_revisor.length() - 2);
        }
        if (!comentario.empty() && comentario.front() == '"' && comentario.back() == '"') {
            comentario = comentario.substr(1, comentario.length() - 2);
        }

        // Inicializar sentimiento
        Sentimiento sent = Sentimiento::neutro;
        Valoracion nuevaValoracion(id_alojamiento, id_valoracion, fecha, id_revisor, nombre_revisor, comentario, sent);
        nuevaValoracion.analizarSentimiento(pal_pos, pal_neg, 0, sent);

        // Insertar valoración
        insertarValoracion(nuevaValoracion, res);
    }

    res = OK;}





//INSERTAR VALORACION:

        // Inserta una valoración en la lista de valoraciones que
        // se pasa como parámetro. Si la valoración se ha podido
        // insertar correctamente, se devuelve OK a través de 'res'.
        // Si la valoración ya existía, se devuelve YA_EXISTE a
        // través de 'res'. La valoración debe insertarse en
        // orden creciente de id de valoración.
        // PARÁMETROS:
        //  - valoracion (E): valoración a insertar
        //  - lista (ES): lista de valoraciones donde se inserta
        //  - res (S): resultado de la operación
        
void Valoraciones::insertarValoracion(const Valoracion &valoracion, Resultado &res) {
    // Crear el nuevo nodo con la valoración
    NodoValoracion* nuevoNodo = new NodoValoracion;
    nuevoNodo->valoracion = valoracion;
    nuevoNodo->sig = nullptr;

    // Si la lista está vacía, simplemente añadir el nodo
    if (valoraciones == nullptr) {
        valoraciones = nuevoNodo;
    } else {
        // Insertar el nodo en la posición correcta para mantener el orden por id_valoracion
        NodoValoracion* actual = valoraciones;
        NodoValoracion* previo = nullptr;

        while (actual != nullptr && actual->valoracion.consultarIdValoracion() < valoracion.consultarIdValoracion()) {
            previo = actual;
            actual = actual->sig;
        }

        if (previo == nullptr) {  // Insertar al principio
            nuevoNodo->sig = valoraciones;
            valoraciones = nuevoNodo;
        } else {  // Insertar en medio o al final
            previo->sig = nuevoNodo;
            nuevoNodo->sig = actual;
        }
    }

    num_valoraciones++;  // Incrementar el contador de valoraciones
    res = OK;            // Resultado de la operación
}








//GUARDAR VALORACIONES

        // Guarda en el fichero cuyo nombre se pasa como parámetro todas las valoraciones
        // de la lista de valoraciones.
        // El formato del fichero es el mismo que para el método 'cargarValoraciones'
        // (véase el fichero 'valoraciones.csv'). Si el fichero puede abrirse para escritura,
        // se guardan en él las valoraciones y se devuelve OK a través de 'res'. Si no,
        // se devuelve FIC_ERROR a través de 'res'.
        // PARÁMETROS:
        //  - nombre_fic (E): nombre del fichero de escritura
        //  - res (S): resultado de la operación
void Valoraciones::guardarValoraciones(const std::string &nombre_fic, Resultado &res) const {
    // Paso 1: Abrir el archivo en modo escritura
    std::ofstream archivo(nombre_fic);
    if (!archivo) {  // Si no se puede abrir el archivo
        res = FIC_ERROR;
        return;
    }

    // Paso 2: Escribir la cabecera
    archivo << "id_alojamiento,id_valoracion,fecha,id_revisor,nombre_revisor,comentario,sentimiento\n";

    // Paso 3: Recorrer la lista de valoraciones y escribirlas en el archivo
    PtrValoracion actual = valoraciones;  // Empezar desde el primer nodo de la lista

    while (actual != nullptr) {  // Recorrer hasta llegar al final de la lista
        // Formatear y escribir los campos
        archivo << actual->valoracion.consultarIdAlojamiento() << ","
                << actual->valoracion.consultarIdValoracion() << ","
                << actual->valoracion.consultarFecha() << ","
                << actual->valoracion.consultarIdRevisor() << ","
                << "\"" << actual->valoracion.consultarNombreRevisor() << "\","
                << "\"" << actual->valoracion.consultarComentarios() << "\",";
        
        // Escribir el sentimiento, según el valor del enum
        switch (actual->valoracion.consultarSentimiento()) {
            case Sentimiento::positivo:
                archivo << "positivo";
                break;
            case Sentimiento::negativo:
                archivo << "negativo";
                break;
            case Sentimiento::neutro:
                archivo << "neutro";
                break;
        }
        archivo << "\n";

        // Avanzar al siguiente nodo
        actual = actual->sig;
    }

    // Si todo va bien, asignar OK al resultado
    res = OK;
}







//ACTUALIZAR SENTIMIENTO

        // Analiza y actualiza el sentimiento de una valoración cuyo identificador se pasa como parámetro.
        // Si la valoración está en la lista de valoraciones del objeto, se analiza y actualiza
        // su sentimiento en función del umbral que se pasa como parámetro; además, se devuelve
        // OK a través de 'res'. Si no existe la valoración, se devuelve NO_EXISTE a través de 'res'.

void Valoraciones::actualizarSentimiento(unsigned id_valoracion, unsigned umbral, Resultado &res) {
    // Paso 1: Buscar la valoración con el id_valoracion proporcionado
    NodoValoracion* actual = valoraciones;
    
    while (actual != nullptr) {
        // Si encontramos la valoración con el id correspondiente
        if (actual->valoracion.consultarIdValoracion() == id_valoracion) {
            
            // Paso 2: Analizar y actualizar el sentimiento de la valoración
            Sentimiento nuevoSentimiento;
            
            // Llamar al método de la clase Valoracion para analizar el sentimiento
            // Pasamos las listas de palabras positivas y negativas y el umbral
            actual->valoracion.analizarSentimiento(pal_pos, pal_neg, umbral, nuevoSentimiento);
            
            // Actualizamos el sentimiento de la valoración usando asignarSentimiento
            actual->valoracion.asignarSentimiento(nuevoSentimiento);
            
            // Paso 3: Devolver OK, ya que hemos actualizado correctamente
            res = OK;
            return;
        }
        
        // Continuamos buscando en el siguiente nodo
        actual = actual->sig;
    }

    // Si no se encontró la valoración, devolvemos NO_EXISTE
    res = NO_EXISTE;}


    



//ACTUALIZAR SENTIMIENTOS

        // Analiza y actualiza el sentimiento de todas las valoraciones a partir de las listas de palabras
        // positivas y negativas actuales almacenadas en el objeto y en función del umbral
        // indicado.
        // Parámetros:
        //  - umbral (E): umbral para clasificar la valoración en positiva, negativa o neutra
   void Valoraciones::actualizarSentimientos(unsigned umbral) {
    // Paso 1: Recorrer todas las valoraciones de la lista vinculada
    NodoValoracion* actual = valoraciones;  // 'valoraciones' es el inicio de la lista de valoraciones

    // Paso 2: Para cada valoración, analizar y actualizar el sentimiento
    while (actual != nullptr) {
        // Analizar el sentimiento de la valoración actual
        Sentimiento nuevoSentimiento;

        // Llamar al método analizarSentimiento para obtener el sentimiento basado en las palabras y el umbral
        actual->valoracion.analizarSentimiento(pal_pos, pal_neg, umbral, nuevoSentimiento);

        // Actualizar el sentimiento de la valoración
        actual->valoracion.asignarSentimiento(nuevoSentimiento);

        // Avanzar al siguiente nodo en la lista
        actual = actual->sig;
    }}




//INSERTAR PALABRA POSITIVA

        // Inserta una nueva palabra en la lista de palabras positivas
        // Parámetros:
        //  - palabra (E): nueva palabra a insertar en la lista de palabras positivas
        //  - res (S): resultado de la operación

void Valoraciones::insertarPalabraPositiva(const std::string &palabra, Resultado &res) {
    // Llamamos al método 'insertar' de la clase Palabras sobre la lista de palabras positivas
    // Si la palabra ya existe, 'insertar' cambiará el valor de 'res' a YA_EXISTE
    pal_pos.insertar(palabra, res);

    // Si 'insertar' devolvió un error (YA_EXISTE), no hacemos nada más
    if (res != OK) {
        return;  // La palabra ya existía, por lo que no la insertamos
    }

    // Si llegamos aquí, la palabra fue insertada correctamente
    // El valor de 'res' ya está seteado a OK por el método 'insertar', por lo que no es necesario cambiarlo
}




//INSERTAR PALABRA NEGATIVA

        // Inserta una nueva palabra en la lista de palabras negativas
        // Parámetros:
        //  - palabra (E): nueva palabra a insertar en la lista de palabras negativas
        //  - res (S): resultado de la operación
void Valoraciones::insertarPalabraNegativa(const std::string &palabra, Resultado &res) {
    // Llamamos al método 'insertar' de la clase Palabras sobre la lista de palabras negativas
    // Si la palabra ya existe, 'insertar' cambiará el valor de 'res' a YA_EXISTE
    pal_neg.insertar(palabra, res);

    // Si 'insertar' devolvió un error (YA_EXISTE), no hacemos nada más
    if (res != OK) {
        return;  // La palabra ya existía, por lo que no la insertamos
    }

    // Si llegamos aquí, la palabra fue insertada correctamente
    // El valor de 'res' ya está seteado a OK por el método 'insertar', por lo que no es necesario cambiarlo
}






//ELIMINAR PALABRA POSITIVA

        // Elimina una nueva palabra de la lista de palabras positivas
        // Parámetros:
        //  - palabra (E): palabra a eliminar de la lista de palabras positivas
        //  - res (S): resultado de la operación
void Valoraciones::eliminarPalabraPositiva(const std::string &palabra, Resultado &res) {
    // Llamamos al método 'eliminar' de la clase Palabras sobre la lista de palabras positivas
    // Si la palabra no existe, 'eliminar' cambiará el valor de 'res' a NO_EXISTE
    pal_pos.eliminar(palabra, res);

    // Si 'eliminar' devolvió un error (NO_EXISTE), no hacemos nada más
    if (res != OK) {
        return;  // La palabra no se encontraba en la lista, por lo que no la eliminamos
    }

    // Si llegamos aquí, la palabra fue eliminada correctamente
    // El valor de 'res' ya está seteado a OK por el método 'eliminar', por lo que no es necesario cambiarlo
}



//ELIMINAR PALABRA NEGATIVA

        // Elimina una nueva palabra de la lista de palabras negativas
        // Parámetros:
        //  - palabra (E): palabra a eliminar de la lista de palabras negativas
        //  - res (S): resultado de la operación

void Valoraciones::eliminarPalabraNegativa(const std::string &palabra, Resultado &res) {
    // Llamamos al método 'eliminar' de la clase Palabras sobre la lista de palabras negativas
    // Si la palabra no existe, 'eliminar' cambiará el valor de 'res' a NO_EXISTE
    pal_neg.eliminar(palabra, res);

    // Si 'eliminar' devolvió un error (NO_EXISTE), no hacemos nada más
    if (res != OK) {
        return;  // La palabra no se encontraba en la lista, por lo que no la eliminamos
    }

    // Si llegamos aquí, la palabra fue eliminada correctamente
    // El valor de 'res' ya está seteado a OK por el método 'eliminar', por lo que no es necesario cambiarlo
}



//NUMERO VALORACIONES 

        // Devuelve el número de valoraciones positivas, negativas y neutras almacenadas.
        // PARÁMETROS:
        //  - positivas (S): número de valoraciones positivas
        //  - negativas (S): número de valoraciones negativas

void Valoraciones::numeroValoraciones(unsigned &positivas, unsigned &negativas, unsigned &neutras) const {
    // Inicializamos los contadores en 0
    positivas = 0;
    negativas = 0;
    neutras = 0;

    // Recorremos todas las valoraciones almacenadas en el objeto
    NodoValoracion* actual = valoraciones; // 'valoraciones' es el puntero a la lista de valoraciones

    // Recorremos la lista de valoraciones
    while (actual != nullptr) {
        // Comprobamos el sentimiento de cada valoración
        if (actual->valoracion.consultarSentimiento() == Sentimiento::positivo) {
            ++positivas;  // Si el sentimiento es positivo, incrementamos el contador de valoraciones positivas
        } else if (actual->valoracion.consultarSentimiento() == Sentimiento::negativo) {
            ++negativas;  // Si el sentimiento es negativo, incrementamos el contador de valoraciones negativas
        } else {
            ++neutras;  // Si el sentimiento es neutro, incrementamos el contador de valoraciones neutras
        }

        // Pasamos al siguiente nodo de la lista
        actual = actual->sig;
    }}




        // Devuelve la lista de los identificadores de todas las valoraciones
        // almacenadas, positivas, negativas y neutras.
        // PARÁMETROS:
        //  - ids_positivas (S): ids de todas las valoraciones positivas
        //  - ids_negativas (S): ids de todas las valoraciones negativas
        //  - ids_neutras (S): ids de todas las valoraciones neutras
void Valoraciones::listaValoraciones(Ids &ids_positivas, Ids &ids_negativas, Ids &ids_neutras) const {
    PtrValoracion actual = valoraciones;  // Comenzar desde el primer nodo de la lista

    // Recorrer la lista enlazada
    while (actual != nullptr) {
        // Obtener el sentimiento de la valoración actual
        Sentimiento sent = actual->valoracion.consultarSentimiento();

        // Clasificar el id de la valoración según el sentimiento
        switch (sent) {
            case Sentimiento::positivo:
                // Verificar si no hemos superado el límite de MAX_NUM_IDS
                if (ids_positivas.num_ids < MAX_NUM_IDS) {
                    ids_positivas.ids[ids_positivas.num_ids++] = actual->valoracion.consultarIdValoracion();
                }
                break;
            case Sentimiento::negativo:
                // Verificar si no hemos superado el límite de MAX_NUM_IDS
                if (ids_negativas.num_ids < MAX_NUM_IDS) {
                    ids_negativas.ids[ids_negativas.num_ids++] = actual->valoracion.consultarIdValoracion();
                }
                break;
            case Sentimiento::neutro:
                // Verificar si no hemos superado el límite de MAX_NUM_IDS
                if (ids_neutras.num_ids < MAX_NUM_IDS) {
                    ids_neutras.ids[ids_neutras.num_ids++] = actual->valoracion.consultarIdValoracion();
                }
                break;
        }

        // Avanzar al siguiente nodo
        actual = actual->sig;
    }
}



//NUMERO PALABRAS

        // Devuelve el número de palabras positivas y negativas almacenadas
        // PARÁMETROS:
        //  - positivas (S): número de palabras positivas
        //  - negativas (S): número de palabras negativas
    void Valoraciones::numeroPalabras(unsigned &positivas, unsigned &negativas) const {
        // Obtener el número de palabras positivas usando el método numPalabras() de la clase Palabras
        positivas = pal_pos.numPalabras();

        // Obtener el número de palabras negativas usando el método numPalabras() de la clase Palabras
        negativas = pal_neg.numPalabras();}




//BUSCAR VALORACION

        // Indica si una valoración, cuyo id se pasa como parámetro,
        // está en la lista de valoraciones.
        // Si está, se devuelve a través de 'valoracion' y se pone 'encontrada' a true
        // PARAMETROS:
        //  - id_valoracion (E): identificador de la valoración a buscar
        //  - valoracion (S): valoración
        //  - encontrada (S): indica si se ha encontrado (true) o no (false) la valoración
            void Valoraciones::buscarValoracion(unsigned id_valoracion, Valoracion &valoracion, bool &encontrada) const {
        PtrValoracion actual = valoraciones;  // Comenzar desde el primer nodo de la lista
        encontrada = false;  // Inicializar como no encontrada

        // Recorrer la lista de valoraciones
        while (actual != nullptr) {
            // Comprobar si el id de la valoración actual coincide con el proporcionado
            if (actual->valoracion.consultarIdValoracion() == id_valoracion) {
                // Si se encuentra la valoración, asignar el objeto valoracion y marcar como encontrada
                valoracion = actual->valoracion;
                encontrada = true;
                return;  // Salir de la función ya que hemos encontrado la valoración
            }

            // Avanzar al siguiente nodo
            actual = actual->sig;
        }

        // Si hemos llegado aquí, significa que la valoración no fue encontrada
        encontrada = false;  }






//INSERTAR VALORACION

        // Inserta una valoración en la lista de valoraciones, en orden creciente
        // de identificador de valoración. No puede haber dos valoraciones repetidas
        // (es decir, con el mismo id de valoración) en el objeto. Si la valoración
        // se ha insertado con éxito, se devuelve OK a través de 'res'. Si la valoración
        // ya existía, se devuelve YA_EXISTE.
        // PARÁMETROS:
        //  - valoracion (E): valoración a insertar
        //  - res (S): resultado de la operación
void Valoraciones::insertarValoracion(const Valoracion &valoracion, Resultado &res) {
        PtrValoracion nuevoNodo = new NodoValoracion{valoracion, nullptr};  // Crear un nuevo nodo con la valoración
        PtrValoracion actual = valoraciones;  // Comenzar desde el primer nodo de la lista

        // Comprobar si la valoración ya existe en la lista
        while (actual != nullptr) {
            if (actual->valoracion.consultarIdValoracion() == valoracion.consultarIdValoracion()) {
                // Si ya existe, asignamos el resultado YA_EXISTE y retornamos
                res = YA_EXISTE;
                delete nuevoNodo;  // Liberar el nodo que intentamos insertar
                return;
            }
            actual = actual->sig;
        }

        // Si la lista está vacía o el nuevo nodo debe ir al principio
        if (valoraciones == nullptr || valoracion.consultarIdValoracion() < valoraciones->valoracion.consultarIdValoracion()) {
            nuevoNodo->sig = valoraciones;  // El nuevo nodo apunta al primer nodo
            valoraciones = nuevoNodo;  // El nuevo nodo se convierte en la cabeza de la lista
            res = OK;
            return;
        }

        // Buscar la posición correcta para insertar la nueva valoración
        actual = valoraciones;
        while (actual->sig != nullptr && actual->sig->valoracion.consultarIdValoracion() < valoracion.consultarIdValoracion()) {
            actual = actual->sig;  // Avanzar al siguiente nodo
        }

        // Insertar el nuevo nodo en la lista
        nuevoNodo->sig = actual->sig;  // El nuevo nodo apunta al siguiente nodo
        actual->sig = nuevoNodo;  // El nodo anterior apunta al nuevo nodo

        // Asignamos OK al resultado ya que la inserción fue exitosa
        res = OK;
    }





//ELIMINAR VALORACION

        // Elimina una valoración cuyo id se pasa como parámetro.
        // Si la valoración se encuentra, se devuelve OK a través de
        // res. Si no, se devuelve NO_EXISTE.
        // PARÁMETROS:
        //  - id_valoracion (E): valoración que quiere elminarse
        //  - res (S): resultado de la operación
void Valoraciones::eliminarValoracion(unsigned id_valoracion, Resultado &res) {
        PtrValoracion actual = valoraciones;  // Comenzamos desde el primer nodo
        PtrValoracion anterior = nullptr;  // Variable para apuntar al nodo anterior

        // Buscar el nodo con el id especificado
        while (actual != nullptr && actual->valoracion.consultarIdValoracion() != id_valoracion) {
            anterior = actual;  // Mover al nodo actual al anterior
            actual = actual->sig;  // Mover al siguiente nodo
        }

        // Si no encontramos el nodo
        if (actual == nullptr) {
            res = NO_EXISTE;  // La valoración no existe
            return;
        }

        // Si el nodo a eliminar es el primero de la lista
        if (anterior == nullptr) {
            valoraciones = actual->sig;  // El primer nodo se elimina, la cabeza apunta al siguiente
        } else {
            // Si el nodo a eliminar no es el primero, se ajustan los punteros
            anterior->sig = actual->sig;
        }

        // Liberamos la memoria del nodo que hemos eliminado
        delete actual;

        res = OK;  // La eliminación fue exitosa
    }





//MODIFICAR VALORACION

        // Modificar una valoración existente con los nuevos datos de la misma que se pasan
        // a través del parámetro 'valoracion'. Si la valoración existe
        // (existe ese id de valoración) se modifica (se sustituye por la nueva
        // valoración) y se devuelve OK a través de 'res'.
        // Si no, se devuelve NO_EXISTE.
        // Parámtros:
        //  - valoracion (E): nueva valoración (para sustituir la existente)
        //  - res (S): resultado de la operación
    void Valoraciones::modificarValoracion(const Valoracion &valoracion, Resultado &res) {
        PtrValoracion actual = valoraciones;  // Comenzamos desde el primer nodo

        // Buscar la valoración con el id especificado
        while (actual != nullptr && actual->valoracion.consultarIdValoracion() != valoracion.consultarIdValoracion()) {
            actual = actual->sig;  // Avanzamos al siguiente nodo
        }

        // Si no encontramos el nodo
        if (actual == nullptr) {
            res = NO_EXISTE;  // La valoración no existe
            return;
        }

        // Si hemos encontrado la valoración, la modificamos
        actual->valoracion = valoracion;  // Reemplazamos la valoración existente por la nueva

        res = OK;  // La modificación fue exitosa
    }



//VALORACIONES ALOJAMIENTO

        // Devuelve la lista de identificadores de valoraciones.
        // PARÁMETROS:
        //  - id_alojamiento (E): identificador de un alojamiento
        //  - ids_valoraciones (S): lista de ids de valoraciones del alojamiento
void Valoraciones::valoracionesAlojamiento(unsigned id_alojamiento, Ids &ids_valoraciones) const {
        PtrValoracion actual = valoraciones;  // Comenzamos desde el primer nodo
        ids_valoraciones.num_ids = 0;  // Inicializamos el contador de IDs en 0

        // Recorrer la lista de valoraciones
        while (actual != nullptr) {
            // Verificamos si la valoración pertenece al alojamiento con el id dado
            if (actual->valoracion.consultarIdAlojamiento() == id_alojamiento) {
                // Si la valoración pertenece al alojamiento, la añadimos a la lista de ids
                if (ids_valoraciones.num_ids < MAX_NUM_IDS) {
                    ids_valoraciones.ids[ids_valoraciones.num_ids] = actual->valoracion.consultarIdValoracion();
                    ids_valoraciones.num_ids++;
                } else {
                    // Si se excede el máximo de IDs, no agregamos más valoraciones
                    break;
                }
            }
            actual = actual->sig;  // Avanzamos al siguiente nodo
        }}




//VALORACIONES REVISOR

        // Devuelve la lista de valoraciones para un determinado revisor.
        // PARÁMETROS:
        //  - id_revisor (E): identificador de un revisor
        //  - ids_valoraciones (S): lista de ids de valoraciones del revisor
 void Valoraciones::valoracionesRevisor(unsigned id_revisor, Ids &ids_valoraciones) const {
        PtrValoracion actual = valoraciones;  // Comenzamos desde el primer nodo
        ids_valoraciones.num_ids = 0;  // Inicializamos el contador de IDs en 0

        // Recorrer la lista de valoraciones
        while (actual != nullptr) {
            // Verificamos si la valoración pertenece al revisor con el id dado
            if (actual->valoracion.consultarIdRevisor() == id_revisor) {
                // Si la valoración pertenece al revisor, la añadimos a la lista de ids
                if (ids_valoraciones.num_ids < MAX_NUM_IDS) {
                    ids_valoraciones.ids[ids_valoraciones.num_ids] = actual->valoracion.consultarIdValoracion();
                    ids_valoraciones.num_ids++;
                } else {
                    // Si se excede el máximo de IDs, no agregamos más valoraciones
                    break;
                }
            }
            actual = actual->sig;  // Avanzamos al siguiente nodo
        }}





//ESCRIBIR


// Escribe por pantalla los datos de todas las valoraciones,
// en el siguiente formato (nótese que se
// usan tabuladores para formatear la salida):
// --- ID alojamiento: <id_alojamiento>
// ID valoración: <id_alojamiento>
// Fecha: <fecha>
// ID revisor: <id_revisor>
// Nombre revisor: <nombre_revisor>
// --- COMENTARIO:
// <comentario>
// *** SENTIMIENTO: positivo/negativo/neutro
void Valoraciones::escribir() const {
        PtrValoracion actual = valoraciones;  // Comenzamos desde el primer nodo

        // Recorrer la lista de valoraciones
        while (actual != nullptr) {
            const Valoracion& valoracion = actual->valoracion;  // Obtenemos la valoración actual

            // Escribimos los datos de la valoración en el formato especificado
            std::cout << "--- ID alojamiento: " << valoracion.consultarIdAlojamiento() << std::endl;
            std::cout << "ID valoración: " << valoracion.consultarIdValoracion() << std::endl;
            std::cout << "Fecha: " << valoracion.consultarFecha() << std::endl;
            std::cout << "ID revisor: " << valoracion.consultarIdRevisor() << std::endl;
            std::cout << "Nombre revisor: " << valoracion.consultarNombreRevisor() << std::endl;

            std::cout << "--- COMENTARIO:" << std::endl;
            std::cout << valoracion.consultarComentarios() << std::endl;

            // Determinamos el sentimiento y lo mostramos
            Sentimiento sentimiento = valoracion.consultarSentimiento();
            std::string sentimiento_str;
            switch (sentimiento) {
                case Sentimiento::positivo:
                    sentimiento_str = "positivo";
                    break;
                case Sentimiento::negativo:
                    sentimiento_str = "negativo";
                    break;
                case Sentimiento::neutro:
                    sentimiento_str = "neutro";
                    break;
            }

            std::cout << "*** SENTIMIENTO: " << sentimiento_str << std::endl;

            // Avanzamos al siguiente nodo
            actual = actual->sig;
        }}





        // ----------- MÉTODOS PRIVADOS




//BUSCAR VALORACION


        // Busca una valoración por su id_valoracion en una lista de valoraciones.
        // Devuelve un puntero 'ptr' apuntando a un nodo que contiene un id de valoración
        // mayor o igual que el que estoy buscando (o a nullptr, si no existe tal nodo),
        // y un puntero 'ant' apuntando al nodo anterior a ese nodo al que apunta 'ptr'
        // (o a nullptr, si 'ptr' apunta al primer nodo de la lista o la lista está vacía).
        // PARÁMETROS:
        //  - id_valoracion (E) : id de la valoración que estoy buscando
        //  - lista (E): lita de valoraciones en la que buscar la valoración
        //  - ptr (S): puntero que apunta a un nodo con id_valoracion mayor o igual que
        //             'id_valoracion'
        //  - ant (S): puntero que apunta al nodo anterior al que apunta 'ptr'
        //  - encontrada (S): indica si ha encontrado ese id de valoración o no
void Valoraciones::buscarValoracion(unsigned id_valoracion,
                                     PtrValoracion lista,
                                     PtrValoracion &ptr,
                                     PtrValoracion &ant,
                                     bool &encontrada) const {
    // Inicializamos 'ant' a nullptr (por si no hay nodo anterior)
    ant = nullptr;
    ptr = lista;  // Comenzamos con el primer nodo de la lista
    encontrada = false;

    // Recorrer la lista de valoraciones
    while (ptr != nullptr) {
        // Comparamos el id de la valoración del nodo actual con el id que buscamos
        if (ptr->valoracion.consultarIdValoracion() == id_valoracion) {
            // Si encontramos la valoración con el id deseado
            encontrada = true;
            return;  // Salimos de la función, hemos encontrado el nodo
        } 
        else if (ptr->valoracion.consultarIdValoracion() > id_valoracion) {
            // Si encontramos un nodo con id mayor que el buscado, salimos
            return;
        }
        
        // Si no hemos encontrado aún el id, seguimos avanzando por la lista
        ant = ptr;  // El nodo actual se convierte en el anterior
        ptr = ptr->sig;  // Avanzamos al siguiente nodo
    }

    // Si no encontramos la valoración, 'ptr' será nullptr y 'encontrada' será false
}





//INSERTAR VALORACION

        // Inserta una valoración en la lista de valoraciones que
        // se pasa como parámetro. Si la valoración se ha podido
        // insertar correctamente, se devuelve OK a través de 'res'.
        // Si la valoración ya existía, se devuelve YA_EXISTE a
        // través de 'res'. La valoración debe insertarse en
        // orden creciente de id de valoración.
        // PARÁMETROS:
        //  - valoracion (E): valoración a insertar
        //  - lista (ES): lista de valoraciones donde se inserta
        //  - res (S): resultado de la operación
void Valoraciones::insertarValoracion(const Valoracion &valoracion, PtrValoracion &lista, Resultado &res) const {
    PtrValoracion ant = nullptr;    // Nodo anterior a 'ptr'
    PtrValoracion ptr = lista;      // Nodo actual que estamos evaluando
    bool encontrada = false;        // Indicador de si ya hemos encontrado una valoración con el id dado

    // Recorrer la lista buscando el lugar adecuado para insertar
    while (ptr != nullptr) {
        unsigned id_actual = ptr->valoracion.consultarIdValoracion();
        unsigned id_nueva = valoracion.consultarIdValoracion();

        if (id_actual == id_nueva) {
            // Si el id de la valoración ya existe, no la insertamos
            encontrada = true;
            break;
        } 
        else if (id_actual > id_nueva) {
            // Si encontramos un id mayor que el que estamos buscando,
            // significa que debemos insertar antes de este nodo
            break;
        }

        // Avanzamos al siguiente nodo
        ant = ptr;
        ptr = ptr->sig;
    }

    if (encontrada) {
        res = YA_EXISTE;  // Ya existe una valoración con ese id
    } else {
        // Crear un nuevo nodo para insertar la valoración
        PtrValoracion nuevo_nodo = new NodoValoracion;
        nuevo_nodo->valoracion = valoracion;
        nuevo_nodo->sig = nullptr;

        // Si la lista está vacía o el nuevo nodo debe ir al principio
        if (ant == nullptr) {
            nuevo_nodo->sig = lista;  // El nuevo nodo apunta al primer nodo de la lista
            lista = nuevo_nodo;       // El nuevo nodo se convierte en el primer nodo
        } else {
            // Insertar entre 'ant' y 'ptr'
            ant->sig = nuevo_nodo;
            nuevo_nodo->sig = ptr;
        }

        res = OK;  // La valoración se ha insertado correctamente
    }}


        
        
        



//ELIMINA VALORACION     


        // Elimina una valoración cuyo identificador se pasa como parámetro
        // de la lista de valoraciones que se pasa también como parámetro.
        // Si se encuentra la valoración en la lista, se elimina y se
        // devuelve OK a través de 'res'. Si no, se devuelve NO_EXISTE
        // a través de 'res'.
        // PARÁMETROS:
        //  - id_valoracion (E): id de la valoración a eliminar
        //  - lista (ES): lista de valoraciones
        //  - res (S): resultado de la operación

void Valoraciones::eliminarValoracion(unsigned id_valoracion, PtrValoracion &lista, Resultado &res) const {
    PtrValoracion ant = nullptr;    // Nodo anterior al nodo que vamos a eliminar
    PtrValoracion ptr = lista;      // Nodo actual que estamos evaluando
    bool encontrada = false;        // Indicador de si hemos encontrado la valoración

    // Recorrer la lista buscando la valoración con el id proporcionado
    while (ptr != nullptr) {
        unsigned id_actual = ptr->valoracion.consultarIdValoracion();  // Obtener el id de la valoración actual

        if (id_actual == id_valoracion) {
            // Si encontramos la valoración con el id buscado
            encontrada = true;
            break;  // Salir del bucle, ya que hemos encontrado la valoración
        }

        // Avanzar al siguiente nodo
        ant = ptr;
        ptr = ptr->sig;
    }

    if (encontrada) {
        // Si es el primer nodo de la lista
        if (ant == nullptr) {
            // Eliminar el primer nodo de la lista
            lista = ptr->sig;  // Hacemos que 'lista' apunte al segundo nodo
        } else {
            // Si no es el primer nodo, se enlaza el nodo anterior con el siguiente
            ant->sig = ptr->sig;
        }

        // Liberar la memoria del nodo eliminado
        delete ptr;

        res = OK;  // La valoración ha sido eliminada correctamente
    } else {
        res = NO_EXISTE;  // La valoración no se encontró en la lista
    }}





//BORRAR VALORACIONES


        // Borra completamente una lista de valoraciones
        // PARÁMETROS:
        //  - lista (ES): lista de valoraciones a borrar
void Valoraciones::borrarValoraciones(PtrValoracion &lista) const {
    PtrValoracion ptr = lista;  // Apuntador al primer nodo de la lista
    while (ptr != nullptr) {
        PtrValoracion temp = ptr;  // Almacenamos el nodo actual
        ptr = ptr->sig;            // Avanzamos al siguiente nodo
        delete temp;               // Liberamos la memoria del nodo actual
    }
    
    // Después de eliminar todos los nodos, dejamos la lista vacía
    lista = nullptr;}






//COPIAR VALORACIONES


        // Devuelve una copia de la lista de valoraciones que se pasa
        // como parámetro.
        // PARÁMETROS:
        //  - lista (E): lista de valoraciones original

Valoraciones::PtrValoracion Valoraciones::copiarValoraciones(PtrValoracion lista) const {
    // Si la lista está vacía, devolvemos nullptr
    if (lista == nullptr) {
        return nullptr;
    }

    // Creamos el primer nodo de la nueva lista copiando el primer nodo de la original
    PtrValoracion nueva_lista = new NodoValoracion;
    nueva_lista->valoracion = lista->valoracion;  // Copiar la valoración
    nueva_lista->sig = nullptr;  // El último nodo no apunta a nada

    // Apuntador para recorrer la nueva lista
    PtrValoracion ptr_nueva = nueva_lista;

    // Recorrer la lista original y copiar cada nodo
    PtrValoracion ptr_original = lista->sig;  // Empezamos desde el segundo nodo de la lista original
    while (ptr_original != nullptr) {
        // Crear un nuevo nodo
        PtrValoracion nuevo_nodo = new NodoValoracion;
        nuevo_nodo->valoracion = ptr_original->valoracion;  // Copiar la valoración
        nuevo_nodo->sig = nullptr;  // El último nodo no apunta a nada

        // Enlazar el nuevo nodo en la nueva lista
        ptr_nueva->sig = nuevo_nodo;

        // Avanzar al siguiente nodo en la nueva lista
        ptr_nueva = nuevo_nodo;

        // Avanzar al siguiente nodo en la lista original
        ptr_original = ptr_original->sig;
    }

    // Devolver el puntero a la nueva lista
    return nueva_lista;
}





} // namespace bblProg2