### Taller n°2 Estructura de Datos

<p>
<strong>Integrante:</strong> Vicente Renato Galaz Palacios <br>
<strong>RUT:</strong> 21.831.202-0 <br>
<strong>Carrera:</strong> Ingeniería en Tecnologías de Información <br>
<strong>Usuario:</strong> whoskanito
</p>

## Estructura del Proyecto  

El proyecto cuenta las siguientes Clases:

### Main
Clase principal de la aplicación. Contiene el método main, encargado de inicializar el sistema.

### Node / NodoDecision
Node: Estructura de dato que sirve como eslabón de una cadena, guarda un dato y un puntero que apunta al siguiente eslabón, utiliza una plantilla "T" para guardar cualquier tipo de dato.
NodoDecision: Estructura para construir el árbol de clasificación de pacientes.

### List, Queue, Stack, ArbolDecision
Implementación de las estructura de datos de forma manual. El "ArbolDecision" se encarga de rutear a los pacientes a su servicio correspondiente.

### Persona, Paciente
Clase padre e hija que representan pacientes dentro del hospital.

### Servicio
Lista de servicios del hospital la cual lleva su propia lista enlazada de pacientes.

## Criterio de clasificación del arbol de decisión

El árbol de decisión funciona de forma binaria, que evalúa las condiciones médicas en orden de prioridad para clasificar a los pacientes.
Se implementó la estructura conceptual del enunciado del proyecto, ya que garantiza evaluar más de 4 atributos médicos (Edad, Trauma, RequiereCirugía, Síntomas Neurológicos, Tipo de Dolor, Temperatura, Dolor y Días de Hospitalización) y asegura una ruta válida hacia los 8 servicios disponibles.

## Criterios de evaluación (Rutas):

Pediatría: Se evalúa primero la Edad < 14. Si es verdadero, ingresa directamente por ser atención prioritaria por edad.

Cirugía / Traumatología: Si hay Trauma == 1, se deriva al bloque de traumatismos. Si RequiereCirugia == 1, va a Cirugía; si no, a Traumatología.

Neurología: Si presenta SintomasNeurologicos == 1, se deriva por alto riesgo cerebral.

Cardiología: Si el TipoDolor == "pecho", se asume riesgo cardíaco y se clasifica a este servicio.

Urgencias: Si la Temperatura >= 38.5 o el Dolor >= 8, el paciente presenta estado crítico y requiere atención de urgencias inmediata.

Hospitalización: Si requiere seguimiento continuo (DiasHospitalizacion >= 2), se le asigna cama.

Medicina General: Si el paciente no cumple con ninguna de las condiciones críticas anteriores, se deriva a atención básica.

## Instrucciones de compilación

Para compilar el proyecto correctamente primero se debe clonar o descargar el repositorio desde GitHub, en el directorio raíz del proyecto ejecutar el siguiente comando en la terminal: 

g++ *.cpp -o hospital

## Instrucciones de ejecución
  
### Forma N°1:

1. Haber compilado el codigo previamente
2. Abrir cmd y utilizar comando "cd" para abrir el directorio del proyecto. Ej: "cd C:\Users\Asus\\...\Taller1EstructuraDeDatos".
3. Ejecutar proyecto escribiendo ".\hospital" en la terminal.

### Forma N°2:
1. Haber compilado el codigo previamente
2. Abrir carpeta del proyecto desde VSCode y abrir su terminal nativa.
3. Ejecutar proyecto escribiendo ".\hospital" en la terminal.

### Forma N°3:
1. Haber compilado el codigo previamente
2. Ejecutar el archivo "hospital.exe" de la carpeta del proyecto.

## Información adicional
Para modificar la lista de pacientes y probar distintos casos de evaluación en el árbol, basta con modificar el archivo pacientes.txt manteniendo el formato separado por punto y coma (;).