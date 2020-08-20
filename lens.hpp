#ifndef LENS_HPP
#define LENS_HPP

template<typename T, typename U>
struct Lens {
public:
  T fst;
  U snd;

  Lens(T t, U u) {
    fst = t;
    snd = u;
  }
};

template<typename T, typename U>
auto view(Lens<T, U> lens) {
  return *lens.fst;
}

template<typename T, typename U>
auto over(Lens<T, U> lens) {
  return *lens.snd;
}

template<typename T, typename U, typename V, typename W>
auto operator+(Lens<T, U> a, Lens<V, W> b) {
  auto v = [&](auto obj) { return (*b.fst)((*a.fst)(obj)); };
  auto o = [&](auto f, auto obj) {
    return (*a.snd)([&](auto obj_) {
      return (*b.snd)(f, obj_);
    }, obj);
  };

  Lens lens(&v, &o);
  return lens;
}

#endif
