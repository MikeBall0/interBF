char t[999], i[999], *h, *p; // t is the tape, i is the instruction set, h is the read/write head, p is the program counter

int isLegalBFChar(char c) {
	return c == '[' || c == ']' || c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',';
}

void memclear(void*mem, int blockSize) {
	while(--blockSize >= 0) *((char*)mem + blockSize) = 0;
}

void q(char*r) { // parse BF, r is the jump pointer
	while(*p) { // while we have a valid instruction
		switch(*p) {
			case '[': q(p++); break; // we open a loop at the next instruction, p will point to the ']' at the end of the loop when it exits, so we can just continue parsing normally
			case ']': if (!*h) return; else p = r; break; // when we hit the end loop if the current write head value is 0 exit the loop, otherwise back to the jump pointer
			case '+': (*h)++; break; // incr the value at the write head
			case '-': (*h)--; break; // decr the value at the write head
			case '>': h++; break; // incr the write head
			case '<': h--; break; // decr the write head
			case '.': putchar(*h); break; // print the char at the write head
			case ',': *h=getchar(); break; // read a value into the cell at the write head
		}
		p ++; // next instruction
	}
}

int main(int argc, char**argv) {
	memclear(t, sizeof(int)*999); // clear our tape
	memclear(i, sizeof(char)*999); // clear our instructions
	int d = 0; // scope depth
	char c; // parse char
	for(;;) { // forever
		while(isLegalBFChar(c = getchar())) { // while the character is legal when \n is hit we will escape this loop, so we always have an exit point
			if (c == '[') d ++; else if (c == ']') d --; // track our depth
			if (d < 0) return 1; // parse error
			*p++ = c;
		}
		if (c == '\n' || c < 0) {
			if (d == 0) { // if we're back in global scope
				p = i; // back to the start
				q(p); // execute
				memclear(i, sizeof(char)*(p-i)); // clear the instruction memory
				p = i; // back to the start
			} else {
				putchar(':'); // prompt for more input
			}
			if (c < 0) return 0; // EOF
		}
	}
}