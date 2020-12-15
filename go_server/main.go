package main

import (
	"fmt"       // Imprimir en consola
	"io"        // Ayuda a escribir en la respuesta
	"io/ioutil" //para leer archivos
	"log"       //Loguear si algo sale mal
	"net/http"  // El paquete HTTP
)

func main() {

	http.HandleFunc("/hola", func(w http.ResponseWriter, peticion *http.Request) {

		b, err := ioutil.ReadFile("/home/javierb/Documentos/sopes1/proyecto1/go server/main.go") // just pass the file name
		if err != nil {
			fmt.Print(err)
		}
		fmt.Println(b)   // print the content as 'bytes'
		str := string(b) // convert content to a 'string'
		io.WriteString(w, str)
		//jiji
	})

	http.HandleFunc("/ruta/un/poco/larga", func(w http.ResponseWriter, peticion *http.Request) {
		io.WriteString(w, "Solicitaste ruta/un/poco/larga")
	})

	direccion := ":8080" // Como cadena, no como entero; porque representa una dirección
	fmt.Println("Servidor listo escuchando en " + direccion)
	log.Fatal(http.ListenAndServe(direccion, nil))
}
