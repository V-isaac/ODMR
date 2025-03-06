// mPrint(Serial, "string", int, long ...);
// Arduino doesn't allow formated print, using custom-made
inline void mPrint(Stream&) {}
template <class H, class... Tail>
void mPrint(Stream& stream, H head, Tail... tail) {
  stream.print(head);
  mPrint(stream, tail...);
}