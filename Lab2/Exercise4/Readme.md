# simple_filter.ino

This program initializes an array of 10 elements by values detected from the ADC pin A0.  The values aren't intented to be anything other than psuedo-random values, although they could be used for audio or some other signal processing.

When a button press is detected, the following math operation is conducted on each array element:

$y[n] = 2 * x[n] - x[n-1]$    ....where n is the index of the array.

![simple_filter](https://github.com/user-attachments/assets/75226db0-6f03-49fd-b9ee-bd57f68e7099)
