# Chapter 4: CML Programming Techniques

## 4.1 Process Networks

I'm skipping the power series math example because it seems very contrived and is not of interest to me.

## 4.2 Client-server programming

### 4.2.1: Unique ID service (p. 73): `id_server.re, id_server_test.re`.

A simple example of wrapping shared state in a thread and presenting an event interface to it.

### 4.2.2/4.2.3: RPC & Guards

This is the section that started to expanded my idea of what an event could encapsulate.
The important idea is that a synced event may immediately do speculative communication,
and then have its commit point be receiving a reply.

### 4.2.4: Clock server

A small example of using guards to initialize work when an event is synced and commit on response.
