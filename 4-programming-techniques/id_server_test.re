open Event;
open QCheck;

let getUId getIdEvent: event int => {
  let ch = new_channel ();
  let _ = Thread.create (fun () => { sync(send ch (sync getIdEvent)); }) ();
  let ev: event int = receive ch;
  ev
};

let allUnique items => List.length items == List.length (List.sort_uniq compare items);

let test =
  QCheck.Test.make
    count::100
    name::"makeUIdServer always unique"
    (list int)
    (fun l => {
      assume (List.length l < 100);
      let getIdEvent = Id_server.makeUIdServer () ();
      let receiveEvs: list (event int) = List.map (fun x => getUId getIdEvent) l;
      let uids: list int = List.map sync receiveEvs;
      allUnique uids
    });

QCheck.Test.check_exn test;

QCheck_runner.run_tests [test];

