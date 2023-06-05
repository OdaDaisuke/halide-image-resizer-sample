package main

import (
	"image"
	"image/png"
	"os"
	"path"
	"testing"
)

func BenchmarkResize(b *testing.B) {
	w := 1920
	h := 1080

	data, err := os.Open(path.Join("../", "assets", "2.png"))
	if err != nil {
		panic(err)
	}

	var img image.Image

	if img, err = png.Decode(data); err != nil {
		panic(err)
	}

	var resizedImg image.Image
	if resizedImg, err = Resize(img, w, h); err != nil {
		panic(err)
	}

	b.ResetTimer()

	Resize(resizedImg, w, h)
}
