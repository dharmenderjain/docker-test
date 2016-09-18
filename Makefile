all: client server

client:
	gcc -o client client.c
	@docker build --tag=client -f client.yml .

server:
	gcc -o server server.c
	@docker build --tag=server -f server.yml .

clean:
	rm -f client server
