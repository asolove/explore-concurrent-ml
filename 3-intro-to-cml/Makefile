FLAGS = -pkg threads.posix -tag thread
TEST_FLAGS = $(FLAGS) -pkg qcheck

default: clean cell_example.native swap_channel_example.native swap_channel_test.native
	./cell_example.native
	./swap_channel_example.native
	./swap_channel_test.native

clean:
	rm -f *.native

cell_example.native:
	rebuild cell_example.native $(FLAGS)

swap_channel_example.native:
	rebuild swap_channel_example.native $(FLAGS)

swap_channel_test.native:
	rebuild swap_channel_test.native $(TEST_FLAGS)
