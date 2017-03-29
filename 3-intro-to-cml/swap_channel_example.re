open Event;

/*
 * What to look for
 * A naive implementation synchronizes on each half of the swap,
 * but does not guarantee that both halves complete with the same pairs.
 * So it allows A -> B -> C -> A. Whereas we want an atomic swap, A<->B, C<->D.
 * So every "Swapped X for Y" should have a corresponding "Swapped Y for X".
 * TODO: learn how to write quickcheck tests in Ocaml to try on lots of cases...
 */
{
  let sc = Swap_channel.create ();

  let trader v =>
    Thread.create
      (fun v => Printf.printf "Swapped %d for %d\n" v (sync (Swap_channel.swap sc v)))
      v;

  let threads = List.map trader [1,2,3,4,5,6];
  List.iter Thread.join threads;
}
