
/* the duration of a dot is the reference unit of time
 * dash is three times the duration of a dot
 * time between dots and dashes within a character is the duration of a dot
 * time between character is three times the duration of a dot 
 * time between words must be seven times the duration of a dot 
 */

const char CLEAR = 0;
const char DOT = 1;
const char DASH = 2;
const char alphabet[26][6]{
  { 'A', DOT, DASH, CLEAR, CLEAR, CLEAR },
  { 'B', DASH, DOT, DOT, DOT, CLEAR },
  { 'C', DASH, DOT, DASH, DOT, CLEAR },
  { 'D', DASH, DOT, DOT, CLEAR, CLEAR },
  { 'E', DOT, CLEAR, CLEAR, CLEAR, CLEAR },
  { 'F', DOT, DOT, DASH, DOT, CLEAR },
  { 'G', DASH, DASH, DOT, CLEAR, CLEAR },
  { 'H', DOT, DOT, DOT, DOT, CLEAR },
  { 'I', DOT, DOT, CLEAR, CLEAR, CLEAR },
  { 'J', DOT, DASH, DASH, DASH, CLEAR },
  { 'K', DASH, DOT, DASH, CLEAR, CLEAR },
  { 'L', DOT, DASH, DOT, DOT, CLEAR },
  { 'M', DASH, DASH, CLEAR, CLEAR, CLEAR },
  { 'N', DASH, DOT, CLEAR, CLEAR, CLEAR },
  { 'O', DASH, DASH, DASH, CLEAR, CLEAR },
  { 'P', DOT, DASH, DASH, DOT, CLEAR },
  { 'Q', DASH, DASH, DOT, DASH, CLEAR },
  { 'R', DOT, DASH, DOT, CLEAR, CLEAR },
  { 'S', DOT, DOT, DOT, CLEAR, CLEAR },
  { 'T', DASH, CLEAR, CLEAR, CLEAR, CLEAR },
  { 'U', DOT, DOT, DASH, CLEAR, CLEAR },
  { 'V', DOT, DOT, DOT, DASH, CLEAR },
  { 'W', DOT, DASH, DASH, CLEAR, CLEAR },
  { 'X', DASH, DOT, DOT, DASH, CLEAR },
  { 'Y', DASH, DOT, DASH, DASH, CLEAR },
  { 'Z', DASH, DASH, DOT, DOT, CLEAR }
};

const unsigned long dotDuration = 500;  // duration [ms] of a dot; basic time unit
const unsigned long tolerance = 400;    // duration that dash, dot or gap may deviate from the ideal length in order to still be recognized
const unsigned long dashDuration = 2 * dotDuration;
const unsigned long shortGap = dotDuration;
const unsigned long mediumGap = 3 * dotDuration;
const unsigned long longGap = 7 * dotDuration;

// current state of the button
enum State {
  UP = 0,
  DOWN = 1
} state;

// time index of the last button state change (from up to down or down to up)
unsigned long lastChange;

// duration of the last button press
unsigned long downDuration;

// dash-dot-sequence of the current character
char character[5];

// index of the next dot/dash in the current character
int characterIndex;

// the next thing to do
enum Action {
  START = 0,
  READ_DASHDOT = 1,
  READ_CHARACTER = 2,
  READ_WORD = 3
} action;
