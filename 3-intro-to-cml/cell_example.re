{
  let updater fn cell => {
    let v = Cell.get cell;
    Cell.put cell (fn v);
  };

  let cell = Cell.create 0;

  let threads = [
    Thread.create (updater (fun x => x + 1)) cell,
    Thread.create (updater (fun x => x + 1)) cell,
    Thread.create (updater (fun x => x + 1)) cell,
    Thread.create (updater (fun x => x + 1)) cell
  ];

  List.iter Thread.join threads;

  Printf.printf "0 + 1 + 1 + 1 + 1 = %d ?!?\n" (Cell.get cell);
}
