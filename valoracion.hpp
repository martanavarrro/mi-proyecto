/***********************************************************************************
 * Fichero valoracion.hpp para la definición de atributos y métodos de la clase
 * Valoracion para la gestión de la información correspondiente a la valoración de
 * un alojamiento turístico.
 *
 * Alumno/a: Marta Navarro López
 * Fecha: 20-11-2024
 * *********************************************************************************/

//// ¡¡¡¡COMPLETAR TODO LO NECESARIO!!!!!

#ifndef _CLASE_VALORACION_
#define _CLASE_VALORACION_
#include <string>
#include <vector>
#include <cctype>
#include "utilidades.hpp"
#include "palabras.hpp"

namespace bblProg2{
             enum Sentimiento
     {neutro,
        negativo,
         positivo };
class Valoracion{
public:

// ------- MÉTODOS PÚBLICOS DE LA CLASE Valoracion





        // Constructor por defecto.
        // Inicializa todos los atributos a sus valores por defecto
        Valoracion();

        // Constructor de copia
        Valoracion(const Valoracion &otra_valoracion);

        // Constructor específico.
        // Inicializa los atributos según los parámetros correspondientes.
        // Parámetros:
        //  - id_alo (E): identificador del alojamiento
        //  - id_val (E): identificador de la valoración
        //  - fec (E): fecha de la valoración (formato AAAA-MM-DD)
        //  - id_rev (E): identificador del revisor
        //  - nom_rev (E): nombre del revisor
        //  - comments (E): la valoración (comentarios)
        //  - sent (E): sentimiento de la valoración
        // PRECONDICIONES:
        //  - La fecha tiene formato correcto (AAAA-MM-DD)
        //  - 'nom_rev' no es una cadena vacía
        //  - 'comments' no es una cadena vacía
        Valoracion(unsigned id_alo,
                   unsigned id_val,
                   const std::string &fec,
                   unsigned id_rev,
                   const std::string &nom_rev,
                   const std::string &comments,
                   Sentimiento sent);

        // Destructor
        ~Valoracion();

        // ----------------- MÉTODOS DE ASIGNACIÓN

        // Asigna el identificador del alojamiento
        // Parámetros:
        //  - id_alo (E): identificador del alojamiento
        void asignarIdAlojamiento(unsigned id_alo);

        // Asigna el identificador de la valoración
        // Parámetros:
        //  - id_val (E): identificador de la valoración
        void asignarIdValoracion(unsigned id_val);

        // Asigna fecha
        // Parámetros:
        //  - fec (E): fecha de la valoración
        // PRECONDICIÓN:
        //  - la fecha tiene formato correcto (AAAA-MM-DD)
        void asignarFecha(const std::string &fec);

        // Asigna el identificador del revisor
        // Parámetros:
        //  - id_rev (E): identificador del revisor
        void asignarIdRevisor(unsigned id_rev);

        // Asigna el nombre del revisor
        // Parámetros:
        //  - nom_rev (E): nombre del revisor
        // PRECONDICIÓN:
        //  - la cadena no está vacía
        void asignarNombreRevisor(const std::string &nom_rev);

        // Asigna la valoración (comentario) al alojamiento
        // Parámetros:
        //  - comment (E): valoración (comentario)
        void asignarComentarios(const std::string &comments);

        // Asigna un valor (positivo, negativo, neutro) al
        // sentimiento de la valoración
        // Parámetros:
        //  - sent (E): sentimiento de la valoración
        void asignarSentimiento(Sentimiento sent);

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
        void analizarSentimiento(const Palabras &pal_pos, const Palabras &pal_neg, unsigned umbral, Sentimiento &sent) const;

        // ----------------- MÉTODOS DE CONSULTA

        // Consulta el id del alojamiento
        unsigned consultarIdAlojamiento() const;

        // Consulta el id de la valoración
        unsigned consultarIdValoracion() const;

        // Consulta el id del revisor
        unsigned consultarIdRevisor() const;

        // Consulta el nombre del revisor
        std::string consultarNombreRevisor() const;

        // Consulta la fecha de la valoración
        std::string consultarFecha() const;

        // Consulta la valoración (comentarios) del alojamiento
        std::string consultarComentarios() const;

        // Consulta el sentimiento de la varloración
        Sentimiento consultarSentimiento() const;

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
        void escribir() const;

        // --------- OPERADORES SOBRECARGADOS (IMPLEMENTADOS POR EL PROFESOR)

        // Operador de asignación de Valoracion.
        // (IMPLEMENTADO POR EL PROFESOR)
        Valoracion &operator=(const Valoracion &otra_valoracion) = default;

        // Operador de comparación de igualdad (necesario para las pruebas unitarios).
        // (IMPLEMENTADO POR EL PROFESOR)
        bool operator==(const Valoracion &otra_valoracion) const;


// -------- PARTE PRIVADA DE LA CLASE Valoracion

private:

        unsigned id_alojamiento;
        unsigned id_valoracion;
        unsigned id_revisor; 
        std::string fecha;    
        std::string nombre_revisor;
        std::string comentario;
        Sentimiento sentimiento;





        // ATRIBUTOS
        // ... id_alojamiento;    // Identificador del alojamiento
        // ... id_valoracion;     // Identificador (único) de la valoración
        // ... fecha;             // Fecha de la valoración
        // ... id_revisor;        // Identificador del revisor de la valoración
        // ... nombre_revisor;    // Nombre del revisor de la valoración
        // ... comentario;        // Valoración (comentario o revisión)
        // ... sentimiento;       // Sentimiento del comentario de la valoración (positivo, negativo, neutro)

;};}
#endif