#include <stdlib.h>
#include "libruntime.h"

const struct halide_type_t halide_uint8_t = { halide_type_uint,  8, 1 };

void free_halide_buffer(halide_buffer_t *buf) {
  if (NULL != buf) {
    free(buf->dim);
  }
  free(buf);
}

void init_rgba_dim(halide_dimension_t *dim, int32_t width, int32_t height) {
  // width
  dim[0].min = 0;
  dim[0].extent = width;
  dim[0].stride = 4;
  dim[0].flags = 0;

  // height
  dim[1].min = 0;
  dim[1].extent = height;
  dim[1].stride = width * 4;
  dim[1].flags = 0;

  // channel
  dim[2].min = 0;
  dim[2].extent = 4;
  dim[2].stride = 1;
  dim[2].flags = 0;
}

halide_buffer_t *create_buffer(unsigned char *data, halide_dimension_t *dim, int dimensions, struct halide_type_t halide_type) {
  halide_buffer_t *buffer = (halide_buffer_t *) malloc(sizeof(halide_buffer_t));
  if(buffer == NULL) {
    return NULL;
  }
  memset(buffer, 0, sizeof(halide_buffer_t));

  buffer->dimensions = dimensions;
  buffer->dim = dim;
  buffer->device = 0;
  buffer->device_interface = NULL;
  buffer->host = data;
  buffer->flags = halide_buffer_flag_host_dirty;
  buffer->type = halide_type;
  return buffer;
}

halide_buffer_t *create_halide_buffer_rgba(unsigned char *data, int width, int height) {
  int dimensions = 3;
  halide_dimension_t *dim = (halide_dimension_t *) malloc(dimensions * sizeof(halide_dimension_t));
  if(NULL == dim) {
    return NULL;
  }
  memset(dim, 0, dimensions * sizeof(halide_dimension_t));
  init_rgba_dim(dim, width, height);

  halide_buffer_t *buf = create_buffer(data, dim, dimensions, halide_uint8_t);
  if(NULL == buf) {
    free(dim);
    return NULL;
  }
  return buf;
}
