/*Cannot create a .cpp file as inline prototypes need the function to be present in the same file as they are defined*/
#ifndef FLYSKY_h
#define FLYSKY_h

class FlySky
{
  private:
    uint8_t CH;
    int CHValue;

  public:
    inline FlySky(const uint8_t)  __attribute__((always_inline));
    inline void begin() __attribute__((always_inline));
    inline bool readSwitch()  __attribute__((always_inline));
};

FlySky::FlySky(const uint8_t CH = -1)
{
  this->CH = CH;
  begin();
}

void FlySky::begin()
{
  pinMode(this->CH, INPUT);
}

bool FlySky::readSwitch()
{
  CHValue = pulseIn(CH, HIGH, 30000);
  CHValue = (int*)CHValue;
  return this->CHValue > 1500 ? true : false;
}

#endif //FLYSKY_h
