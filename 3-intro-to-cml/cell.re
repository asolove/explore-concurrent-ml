/* An updateable cell
 * This code follows a normal pattern for CML client-server interaction:
 * - An abstract type holds references to the channels needed
 * - Use of those channels is solely through functions in our module
 * - The client functions run in the client thread and block on sync.
 *
 * But, this data type has a critical problem in concurrent programs.
 * Clients only block on the get or put individually, so multiple threads
 * can interleave gets/puts and do non-atomic updates. To prevent this,
 * we'll need to change to an MVar, which only allows one thread to get
 * the current value at a time.
 */

type request 'a =
  | Get
  | Put 'a;

type t 'a = {
  reqCh: Event.channel (request 'a),
  replyCh: Event.channel 'a
};

let get {reqCh, replyCh} => {
  Event.sync (Event.send reqCh Get);
  Event.sync (Event.receive replyCh);
};

let put {reqCh, replyCh} v => {
  Event.sync (Event.send reqCh (Put v));
};

let create v => {
  let reqCh = Event.new_channel ();
  let replyCh = Event.new_channel ();

  Thread.create (fun v => {
    let rec loop = fun state => {
      switch (Event.sync (Event.receive reqCh)) {
        | Get => {
          Event.sync (Event.send replyCh state);
          loop state;
        }
        | Put state' => {
          loop state';
        }
      }
    };
    loop v;
  }) v;

  {reqCh, replyCh}
};
