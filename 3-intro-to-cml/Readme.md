# Chapter 3: An Introduction to Concurrent ML

## Updatable cells, p42-44

The first example of hiding a concurrent channel-based implementation behind
an abstract data type and functional API. This updatable cell is not actually
a good primitive for concurrent programming, but is a simple first example.

See `cell.rei` for the signature, `cell.re` for the implementation, and an
example program with interleaving problems in `cell_example.re`.
