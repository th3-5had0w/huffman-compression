### Demo 1

Test với file mẫu hehe.txt có 10 bytes với content là heheboiiii đã được nén tạo thành các bits ngắn hơn

-> [Đọc file](https://github.com/th3-5had0w/huffman-compression/blob/master/fileHandler.cpp#L13)

-> [Tính frequency của các chars](https://github.com/th3-5had0w/huffman-compression/blob/master/compressor.cpp#L33)

-> [Đưa vào priority queue](https://github.com/th3-5had0w/huffman-compression/blob/master/compressor.cpp#L67)

-> [Tạo ra huffmancode từ queue](https://github.com/th3-5had0w/huffman-compression/blob/master/compressor.cpp#L88)

-> [Chuyển content gốc thành bitstring](https://github.com/th3-5had0w/huffman-compression/blob/master/compressor.cpp#L91)

-> [Padding đến khi bitstring có độ dài là bội của 8](https://github.com/th3-5had0w/huffman-compression/blob/master/compressor.cpp#L102)

-> [Xử lý mỗi 8 bits](https://github.com/th3-5had0w/huffman-compression/blob/master/fileHandler.cpp#L59)

-> [Sử dụng library bitset để convert bitstring sang unsigned char](https://github.com/th3-5had0w/huffman-compression/blob/master/fileHandler.cpp#L64)

-> [Viết vào file mới](https://github.com/th3-5had0w/huffman-compression/blob/master/fileHandler.cpp#L37)

-> file text 10 bytes -> file text 4 bytes (lossless) :D