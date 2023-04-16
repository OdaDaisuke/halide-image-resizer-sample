// +build ignore.                                                                                                                                                                 

#include <Halide.h>
#include <halide_image_io.h>

using namespace Halide;
using namespace Halide::Tools;

Func scale(Func input, Param<int32_t> width, Param<int32_t> height, Param<int32_t> scale_width, Param<int32_t> scale_height) {
  Var x("x"), y("y"), ch("ch");

  Func to_f = Func("to_float");
  to_f(x, y, ch) = cast<float>(input(x, y, ch));

  Expr dx = cast<float>(width) / cast<float>(scale_width);
  Expr dy = cast<float>(height) / cast<float>(scale_height);

  Func scale = Func("scale");
  Expr px = cast<int>((x + 0.5f) * dx);
  Expr py = cast<int>((y + 0.5f) * dy);
  scale(x, y, ch) = to_f(px, py, ch);

  Func out = Func("out");
  out(x, y, ch) = cast<uint8_t>(0);
  out(x, y, 0) = cast<uint8_t>(scale(x, y, 0));
  out(x, y, 1) = cast<uint8_t>(scale(x, y, 1));
  out(x, y, 2) = cast<uint8_t>(scale(x, y, 2));
  out(x, y, 3) = cast<uint8_t>(255);
  return out;
}

int main(int argc, char **argv) {
  ImageParam src(type_of<uint8_t>(), 3, "src");

  Param<int32_t> width{"width", 1920};
  Param<int32_t> height{"height", 1080};
  Param<int32_t> scale_width{"scale_width", 400};
  Param<int32_t> scale_height{"scale_height", 300};

  // in rgba
  src.dim(0).set_stride(4);
  src.dim(2).set_stride(1);
  src.dim(2).set_bounds(0, 4);

  Func fn = scale(src.in(), width, height, scale_width, scale_height);

  OutputImageParam out = fn.output_buffer();
  // out rgba
  out.dim(0).set_stride(4);
  out.dim(2).set_stride(1);
  out.dim(2).set_bounds(0, 4);

  std::vector<Target::Feature> features;
  features.push_back(Target::SSE41);
  features.push_back(Target::Feature::NoRuntime);
  // generate runtime
  {
    Func runtime = Func("runtime");
    runtime() = 0;

    Target target;
    target.os = Target::OSX;
    target.arch = Target::X86;
    target.bits = 64;
    target.set_features(features);
    runtime.compile_to_static_library(
      "libruntime",
      {},
      "runtime",
      target.without_feature(Target::Feature::NoRuntime)
    );
  }
  // generate scale
  {
    std::vector<Argument> args = {src, width, height, scale_width, scale_height};
    Target target;
    target.os = Target::OSX;
    target.arch = Target::X86;
    target.bits = 64;
    target.set_features(features);
    fn.compile_to_static_library(
      "libscale",
      {src, width, height, scale_width, scale_height},
      "scale",
      target
    );
  }

  return 0;
}
