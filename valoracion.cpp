/***********************************************************************************
 * Fichero valoracion.cpp para la implementación de métodos de la clase
 * Valoracion para la gestión de la información correspondiente a la valoración de
 * un alojamiento turístico.
 *
 * Alumno/a: 
 * Fecha: 
 * *********************************************************************************/

#include "valoracion.hpp"
#include "palabras.hpp"
#include <string>
#include <cctype>
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

// ------- FUNCIONES AUXILIARES PARA LA IMPLEMENTACIÓN DE LOS MÉTODOS
// (IMPLEMENTADAS POR EL PROFESORADO)

// ------- FUNCIONES AUXILIARES PARA LA IMPLEMENTACIÓN DE LOS MÉTODOS
// (IMPLEMENTADAS POR EL PROFESORADO)

namespace
{
    bool fechaCorrecta(const string &fec)
    {
        bool correcta = fec.size() == 10;

        correcta = isdigit(fec[0]) &&
                   isdigit(fec[1]) &&
                   isdigit(fec[2]) &&
                   isdigit(fec[3]) &&
                   isdigit(fec[5]) &&
                   isdigit(fec[6]) &&
                   isdigit(fec[8]) &&
                   isdigit(fec[9]) &&
                   fec[4] == '-' &&
                   fec[7] == '-';

        return correcta;
    }

    void escribirSentimiento(bblProg2::Sentimiento sent)
    {
        switch (sent)
        {
        case bblProg2::neutro:
            cout << "neutro";
            break;
        case bblProg2::negativo:
            cout << "negativo";
            break;
        case bblProg2::positivo:
            cout << "positivo";
            break;
        }
    }

    // Limpia un comentario (cadena de caracteres):
    //  - elimina signos de puntuación
    //  - convierte todo a minúscula
    //  - elimina espacios repetidos
    //  - elimina todos los espacios iniciales y finales
    // PARÁMETROS:
    //  - comentario (E): comentario original
    //  - procesado (S): comentario procesado (limpio)
    void procesarComentario(const string &comentario, string &procesado)
    {
        procesado = comentario;

        while (!procesado.empty() && procesado[0] == ' ')
        {
            procesado.erase(0, 1);
        }

        while (!procesado.empty() && procesado.back() == ' ')
        {
            procesado.pop_back();
        }

        unsigned i = 0;
        while (i < procesado.size())
        {
            if (!ispunct(procesado[i]))
            {
                if (procesado[i] == ' ')
                {
                    if (i > 0 && procesado[i - 1] == ' ')
                    {
                        procesado.erase(i, 1);
                    }
                    else
                    {
                        i++;
                    }
                }
                else
                {
                    procesado[i] = tolower(procesado[i]);
                    i++;
                }
            }
            else
            {
                procesado.erase(i, 1);
            }
        }
    }

} // namespace

// ----------------------------------------------

namespace bblProg2
{  

    // ---------- OPERADORES SOBRECARGADOS (IMPLEMENTADOS POR EL PROFESORADO)

    // Operador de comparación de igualdad (necesario para las pruebas unitarios)
    bool Valoracion::operator==(const Valoracion &otra_valoracion) const
    {
        return (id_alojamiento == otra_valoracion.id_alojamiento &&
                id_valoracion == otra_valoracion.id_valoracion &&
                fecha == otra_valoracion.fecha &&
                id_revisor == otra_valoracion.id_revisor &&
                nombre_revisor == otra_valoracion.nombre_revisor &&
                comentario == otra_valoracion.comentario &&
                sentimiento == otra_valoracion.sentimiento);
    }

    // -------------------------------------------------------------------

    // IMPLEMENTACIÓN DE LOS MÉTODOS PÚBLICOS Y PRIVADOS

    //Constructor por defecto
    Valoracion::Valoracion(): id_alojamiento{}, id_valoracion{},id_revisor{}, fecha{},nombre_revisor{}, comentario{}, sentimiento{}{}

    // Constructor de copia
    
    Valoracion:: Valoracion(const Valoracion &otra_valoracion): id_alojamiento{otra_valoracion.id_alojamiento}, 
    id_valoracion{otra_valoracion.id_valoracion},id_revisor{otra_valoracion.id_revisor}, fecha{otra_valoracion.fecha},nombre_revisor{otra_valoracion.nombre_revisor}, 
    comentario{otra_valoracion.comentario}, sentimiento{otra_valoracion.sentimiento}{}

    //Constructor específico

Valoracion::Valoracion(unsigned id_alo,
                       unsigned id_val,
                       const std::string &fec,
                       unsigned id_rev,
                       const std::string &nom_rev,
                       const std::string &comments,
                       Sentimiento sent)
    : id_alojamiento{id_alo}, id_valoracion{id_val}, id_revisor{id_rev}, fecha{fec}, 
      nombre_revisor{nom_rev}, comentario{comments}, sentimiento{sent} { assert(fechaCorrecta(fec));} 




    

    // Destructor
        Valoracion::~Valoracion(){}




        // ----------------- MÉTODOS DE ASIGNACIÓN

        // Asigna el identificador del alojamiento
        // Parámetros:
        //  - id_alo (E): identificador del alojamiento
        void Valoracion::asignarIdAlojamiento(unsigned id_alo){
            id_alojamiento=id_alo;
        }

        // Asigna el identificador de la valoración
        // Parámetros:
        //  - id_val (E): identificador de la valoración
        void Valoracion::asignarIdValoracion(unsigned id_val){
            id_valoracion=id_val;
        }

        // Asigna fecha
        // Parámetros:
        //  - fec (E): fecha de la valoración
        // PRECONDICIÓN:
        //  - la fecha tiene formato correcto (AAAA-MM-DD)
        void Valoracion::asignarFecha(const std::string &fec){
            fecha=fec;
        }

        // Asigna el identificador del revisor
        // Parámetros:
        //  - id_rev (E): identificador del revisor
        void Valoracion:: asignarIdRevisor(unsigned id_rev){
            id_revisor=id_rev;
        }

        // Asigna el nombre del revisor
        // Parámetros:
        //  - nom_rev (E): nombre del revisor
        // PRECONDICIÓN:
        //  - la cadena no está vacía
        void Valoracion::asignarNombreRevisor(const std::string &nom_rev){
            nombre_revisor=nom_rev;
        }

        // Asigna la valoración (comentario) al alojamiento
        // Parámetros:
        //  - comment (E): valoración (comentario)
        void Valoracion:: asignarComentarios(const std::string &comments){
            comentario=comments;
        }

        // Asigna un valor (positivo, negativo, neutro) al
        // sentimiento de la valoración
        // Parámetros:
        //  - sent (E): sentimiento de la valoración
        void Valoracion::asignarSentimiento(Sentimiento sent){
            sentimiento=sent;
        }





//ANALIZAR SENTIMIENTO

        // Analiza y devuelve el sentimiento de la valoración.
        // Para ello:
        // 1) Cuenta cuántas palabras positivas y negativas hay en el comentario
        //    de la valoracion, a partir de las listas de palabras positivas y negativas
        //    que se reciben como parámetro.
        // 2) Si el número de palabras positivas supera (es mayor) en un determinado umbral
        //    al número de palabras negativas, se asigna sentimiento positivo a la valoración,
        // 3) si no, si el número de palabras negativas supera (es mayor) en un determinado umbral
        //    al número de palabras positivas, se asigna sentimiento negativo a la valoración,
        // 4) si no, se asigna sentimiento neutro a la valoración.
        //
        // El comentario debe preprocesarse antes de ser clasificado, para 1) eliminar
        // los signos de puntuación que contiene, 2) eliminar espacios repetidos, eliminar
        // todos los espacios que haya al principio o al final del comentario, y
        // 3) convertir todas las letras en minúsculas. Para ello, puede usarse la
        // función auxiliar 'preprocesarComentario'.
        // Parámetros:
        //  - pal_pos (E): lista de palabras positivas
        //  - pal_neg (E): lista de palabras negativas
        //  - umbral (E): umbral para la determinación del sentimiento
        //  - sent (S): sentimiento de la valoración



std::vector<std::string> dividirEnPalabras(const std::string &texto) {
    std::vector<std::string> palabras;
    std::string palabra;

    for (char c : texto) {
        if (c != ' ') {
            palabra += c;
        } else if (!palabra.empty()) {
            palabras.push_back(palabra);
            palabra.clear();
        }
    }

    // Agregar la última palabra, si existe
    if (!palabra.empty()) {
        palabras.push_back(palabra);
    }

    return palabras;
}


void Valoracion::analizarSentimiento(const Palabras &pal_pos, const Palabras &pal_neg, unsigned umbral, Sentimiento &sent) const {
        //Procesar el comentario
        std::string procesado;
        procesarComentario(comentario, procesado);

        // Dividir el comentario en palabras
        std::vector<std::string> palabras = dividirEnPalabras(procesado);

        // Paso 3: Contar palabras positivas y negativas
        unsigned countPos = 0, countNeg = 0;

for (const std::string &pal : palabras) {
    for (std::size_t i = 0; i < pal_pos.numPalabras(); ++i) {
        if (pal == pal_pos[i]) {
            ++countPos;
            break;
        }
    }

    for (std::size_t i = 0; i < pal_neg.numPalabras(); ++i) {
        if (pal == pal_neg[i]) {
            ++countNeg;
            break;
        }
    }
}


        //Determinar el sentimiento
        if (countPos > countNeg + umbral) {
            sent = positivo;
        } else if (countNeg > countPos + umbral) {
            sent = negativo;
        } else {
            sent = neutro;
        }    }







        // ----------------- MÉTODOS DE CONSULTA

// Consulta el id del alojamiento
unsigned Valoracion::consultarIdAlojamiento() const {
    return id_alojamiento; 
}

// Consulta el id de la valoración
unsigned Valoracion::consultarIdValoracion() const {
    return id_valoracion;  
}

// Consulta el id del revisor
unsigned Valoracion::consultarIdRevisor() const {
    return id_revisor;  
}

// Consulta el nombre del revisor
std::string Valoracion::consultarNombreRevisor() const {
    return nombre_revisor; 
}

// Consulta la fecha de la valoración
std::string Valoracion::consultarFecha() const {
    return fecha;
}

// Consulta la valoración (comentarios) del alojamiento
std::string Valoracion::consultarComentarios() const {
    return comentario;  
}

// Consulta el sentimiento de la valoración
Sentimiento Valoracion::consultarSentimiento() const {
    return sentimiento; 
}


        // Escribe por pantalla los datos de la valoración,
        // en el siguiente formato (nótese que se
        // usan tabuladores para formatear la salida):
        //  ID alojamiento:      <id_alojamiento>
        //  ID valoración:       <id_alojamiento>
        //  Fecha:               <fecha>
        //  ID revisor:          <id_revisor>
        //  Nombre revisor:      <nombre_revisor>
        //  --- COMENTARIO:
        //  <comentario>
        //  *** SENTIMIENTO: positivo/negativo/neutro

      void Valoracion::escribir() const {
    // Imprimir los datos de la valoración en el formato solicitado
    std::cout << "ID alojamiento:\t" << id_alojamiento << std::endl;
    std::cout << "ID valoración:\t" << id_valoracion << std::endl;
    std::cout << "Fecha:\t\t" << fecha << std::endl;
    std::cout << "ID revisor:\t" << id_revisor << std::endl;
    std::cout << "Nombre revisor:\t" << nombre_revisor << std::endl;
    
    // Encabezado de comentario
    std::cout << "--- COMENTARIO:\n";
    std::cout << comentario << std::endl;

    // Escribir el sentimiento
    std::cout << "*** SENTIMIENTO:\t";
    switch (sentimiento) {
        case positivo:
            std::cout << "positivo";
            break;
        case negativo:
            std::cout << "negativo";
            break;
        case neutro:
            std::cout << "neutro";
            break;
        default:
            std::cout << "desconocido";  
            break;
    }
    std::cout << std::endl;
}


} // namespace bblProg2
