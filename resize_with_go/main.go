package main

import (
	"golang.org/x/image/draw"
	"image"
	"image/png"
	"io"
	"os"
	"path"
)

func main() {
	data, err := os.Open(path.Join("../", "assets", "2.png"))
	if err != nil {
		panic(err)
	}

	resizeByGo(data, 1920, 1080)
}

func resizeByGo(r io.Reader, w, h int) (*io.PipeReader, error) {
	var img image.Image
	var err error

	if img, err = png.Decode(r); err != nil {
		return nil, err
	}

	var resizedImg image.Image
	if resizedImg, err = Resize(img, w, h); err != nil {
		return nil, err
	}

	pr, pw := io.Pipe()

	go func() {
		if err = png.Encode(pw, resizedImg); err != nil {
			return
		}
		pw.Close()
	}()

	return pr, nil
}

func Resize(img image.Image, x int, y int) (image.Image, error) {
	rect := image.Rect(0, 0, x, y)

	resizedImg := image.NewRGBA(rect)
	draw.CatmullRom.Scale(resizedImg, rect, img, img.Bounds(), draw.Over, nil)
	return resizedImg, nil
}
