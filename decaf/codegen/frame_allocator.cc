#include "frame_allocator.hh"

#include <cmath>
Frame_allocator::Frame_allocator(Segment segment, Frame_growth frame_growth)
  : segment(segment), frame_growth(frame_growth), direction((int)frame_growth), start(0), offset(0) {
  if (frame_growth == Frame_growth::Upwards || segment == gpRelative)
    return;
  start = offset = -CodeGenerator::VarSize;
}

Location* Frame_allocator::allocate(int size, char* name) {
  generate_next_offset(size);
  return new Location(segment, offset, name);
}

void Frame_allocator::generate_next_offset(int size) {
  offset += size * direction;
}

int Frame_allocator::size() const {
  return abs(offset - start);
}
