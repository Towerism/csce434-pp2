#ifndef FRAME_ALLOCATOR_H
#define FRAME_ALLOCATOR_H

#include <codegen/codegen.hh>
#include <arch/tac.hh>
enum class Frame_growth : int {
  Upwards = 1, Downwards = -1
};
class Frame_allocator {
public:
  Frame_allocator(Segment segment, Frame_growth frame_growth);

  Location* allocate(int size, char* name);
  int size() const;

private:
  Segment segment;
  Frame_growth frame_growth;
  int direction;
  int start, offset;

  void generate_next_offset(int size);
};

#endif /* FRAME_ALLOCATOR_H */
