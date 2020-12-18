package main

import (
	"fmt" // Imprimir en consola
	"io/ioutil"
	"log"           //Loguear si algo sale mal
	"net/http"      // El paquete HTTP
	"path/filepath" //para leer archivos
	"time"

	"github.com/gorilla/websocket" //socket
)

var clients = make(map[*websocket.Conn]bool) // connected clients
var broadcast = make(chan Message)

// Configure the upgrader
var upgrader = websocket.Upgrader{}

// Define our message object
type Message struct {
	Total string `json:"totalram"`
	Used  string `json:"usedram"`
	Free  string `json:"freeram"`
}

func reverse(w http.ResponseWriter, r *http.Request) {
	ws, _ := upgrader.Upgrade(w, r, nil)

	defer ws.Close()
	// Register our new client
	clients[ws] = true
	for {
		// Receive message
		//mt, message, _ := ws.ReadMessage()
		log.Printf("Nuevo cliente registrado. ")

		// Response message
		//log.Printf("Message sent: %s", str)
	}
}
func handleMessages() {
	for {
		// Grab the next message from the broadcast channel

		b, err := ioutil.ReadFile("/proc/mysysinfo") // just pass the file name
		if err != nil {
			fmt.Print(err)
		}
		//fmt.Println(b) // print the content as 'bytes'
		str := string(b)
		var nuevo Message
		// Read in a new message as JSON and map it to a Message object
		broadcast <- nuevo
		//n := len(message)
		time.Sleep(5 * time.Second)

		msg := <-broadcast
		// Send it out to every client that is currently connected
		for client := range clients {
			err2 := client.WriteJSON(msg)
			if err != nil {
				log.Printf("error: %v", err)
				client.Close()
				delete(clients, client)
			}
		}
	}
}
func main() {
	http.HandleFunc("/home", func(res http.ResponseWriter, req *http.Request) {
		http.ServeFile(res, req, filepath.Join("./home.html"))
	})
	http.HandleFunc("/reverse", reverse)
	go handleMessages()
	/*
		http.HandleFunc("/hola", func(w http.ResponseWriter, peticion *http.Request) {

			b, err := ioutil.ReadFile("") // just pass the file name
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
	*/
	direccion := ":8080" // Como cadena, no como entero; porque representa una dirección
	fmt.Println("Servidor listo escuchando en " + direccion)
	log.Fatal(http.ListenAndServe(direccion, nil))
}
