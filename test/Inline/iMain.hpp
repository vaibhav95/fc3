template <class T>
void test::print(T start, T end)
{
  for (T i = start; i < end; i++)
  {
    std::cout << "[" << (i - start) << "]"
              << " = " << *i << std::endl;
  }
  std::cout << std::endl;
}
