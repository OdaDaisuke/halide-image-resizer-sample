package main

import (
	"io"
	"log"
	"net/http"
	"os/exec"
	"path/filepath"
	"strconv"
)

func main() {
	log.Println("starting server")

	http.HandleFunc("/image", getImage)

	log.Println("app started on port 8080")
	http.ListenAndServe(":8080", nil)
}

func getImage(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodGet {
		w.WriteHeader(http.StatusMethodNotAllowed)
		return
	}

	queryParams := r.URL.Query()
	queryFile := queryParams.Get("f")
	if queryFile == "" {
		http.Error(w, "no `?f` specified", http.StatusInternalServerError)
		return
	}

	queryWidth := queryParams.Get("w")
	queryHeight := queryParams.Get("h")
	width, _ := strconv.Atoi(queryWidth)
	height, _ := strconv.Atoi(queryHeight)

	fileEXT := filepath.Ext(queryFile)
	responseContentType := "image/jpeg"
	if fileEXT == "png" {
		responseContentType = "image/png"
	}

	destFilename, err := execEncode(queryFile, width, height)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	imageFile, err := http.Dir(".").Open(destFilename)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer imageFile.Close()

	imageData, err := io.ReadAll(imageFile)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", responseContentType)
	_, err = w.Write(imageData)
	if err != nil {
		log.Printf("Error:%v", err.Error())
	}
}

func execEncode(filename string, width, height int) (string, error) {
	w := strconv.Itoa(width)
	h := strconv.Itoa(height)
	destFilename, err := exec.Command("./resizer", filename, w, h).Output()
	if err != nil {
		return "", err
	}
	return string(destFilename), nil
}
