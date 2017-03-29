open Event;
open QCheck;

let swappers (vs: list int): list (int, int) => {
  let swapCh = Swap_channel.create ();
  let resultCh = new_channel ();
  let swapper v => Thread.create (fun v1 => {
    let swapEv = Swap_channel.swap swapCh v1;
    let afterSwap = fun v2 => sync (send resultCh (v1, v2));
    sync (wrap swapEv afterSwap);
  }) v;
    
  let threads = List.map swapper vs;
  List.map (fun _ => sync (receive resultCh)) threads;
};

let rec pairs = fun
  | [] => true
  | [p] => false
  | [(a,b), ...rest] =>
    List.mem_assoc b rest && List.assoc b rest == a && pairs (List.remove_assoc b rest);

let test =
  QCheck.Test.make
    count::10
    name::"swap_is_atomic"
    (list int)
    (fun l => {
      assume (List.length l mod 2 == 0);
			pairs (swappers l);
    });

QCheck.Test.check_exn test;

QCheck_runner.run_tests [test];

