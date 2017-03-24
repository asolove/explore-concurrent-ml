open Printf;

type buffer 'a = {
  data: ref (option 'a),
  mu: Mutex.t,
  dataAvail: Condition.t,
  dataEmpty: Condition.t
};

let withLock = fun mu fn arg => {
  Mutex.lock mu;
  let r = fn arg;
  Mutex.unlock mu;
  r;
};

let create => {
  {
    data: ref None,
    mu: Mutex.create(),
    dataAvail: Condition.create(),
    dataEmpty: Condition.create()
  }
};

let insert {data, mu, dataAvail, dataEmpty} v => {
  let rec doInsert = fun
    | None => { data := Some v; Condition.signal dataAvail; }
    | Some v => { Condition.wait dataEmpty mu; doInsert !data; };

  withLock mu doInsert !data
};

let get {data, mu, dataAvail, dataEmpty} => {
  let rec doGet = fun
    | None => { Condition.wait dataAvail mu; doGet !data; }
    | Some v => { data := None; Condition.signal dataEmpty; v };

  withLock mu doGet !data
};

let writer b => {
  Thread.create (fun v => {
    printf "Writer %d: About to put %d\n" v v;
    insert b v;
    printf "Writer %d: Did put %d\n" v v;
  });
};

let reader b => {
  Thread.create (fun n => {
    printf "Reader %d: About to receive\n" n;
    let v = get b;
    printf "Reader %d: Received %d\n" n v;
  });
};


{
  let buffer = create ();
  let messages = [1,2,3];
  let writers = List.map (Thread.create (writer buffer)) messages;
  let readers = List.map (Thread.create (reader buffer)) messages;
  List.iter Thread.join (List.concat [writers, readers]);
}
