default: cell_example.native swap_channel_example.native
	./cell_example.native
	./swap_channel_example.native

cell_example.native:
	rebuild cell_example.native -pkg threads.posix -tag thread

swap_channel_example.native:
	rebuild swap_channel_example.native -pkg threads.posix -tag thread
