LEX := lex
GRAMMAR := grammar
OUT := program
TESTS_DIR := tests
VM_FILE := virtual-machine

.PHONY: all test clean

all: $(OUT)

$(GRAMMAR).tab.c $(GRAMMAR).tab.h: $(GRAMMAR).y
	bison -d $(GRAMMAR).y

$(LEX).yy.c: $(LEX).l
	flex $(LEX).l

$(OUT): $(GRAMMAR).tab.c $(LEX).yy.c
	g++ -o $(OUT) $(GRAMMAR).tab.c $(LEX).yy.c $(VM_FILE).cpp -lm

test: $(OUT)
	@echo "Running tests..."; \
	for file in $(TESTS_DIR)/*; do \
		if [ -f "$$file" ]; then \
			output=$$(./$(OUT) "$$file" 2>&1); \
			last_line=$$(echo "$$output" | tail -n 1); \
			if [ "$$last_line" != "Parsing completed successfully!" ]; then \
				echo "Test failed for $$file"; \
			else \
				echo "Test passed for $$file"; \
			fi; \
		fi; \
	done

clean:
	rm -f $(GRAMMAR).tab.c $(GRAMMAR).tab.h $(LEX).yy.c $(OUT) $(VM_FILE)