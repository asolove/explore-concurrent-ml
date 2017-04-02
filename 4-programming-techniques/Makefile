FLAGS = -pkg threads.posix -tag thread
TEST_FLAGS = $(FLAGS) -pkg qcheck

default: clean id_server.native id_server_test.native
	./id_server_test.native

clean:
	rm -f *.native

id_server_test.native:
	rebuild id_server_test.native $(TEST_FLAGS)

id_server.native:
	rebuild id_server.native $(FLAGS)
