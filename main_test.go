package main

import (
	"os"
	"path"
	"testing"
)

func BenchmarkScale(b *testing.B) {
	w := 1920
	h := 1080

	data, err := os.ReadFile(path.Join("assets", "2.png"))
	if err != nil {
		panic(err)
	}

	src, err := pngToRGBA(data)
	if err != nil {
		panic(err)
	}

	b.ResetTimer()

	Scale(src, w, h)
}
