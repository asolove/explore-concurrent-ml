module Semaphore = Core_extended.Std.Semaphore;

type buffer 'a = {
  data: ref (option 'a),
  emptySem: Semaphore.t bool,
  fullSem: Semaphore.t bool
};

fun create : buffer 'a => {
  { data: ref None,
    emptySem: Semaphore.init(Some true),
    fullSem: Semaphore.init(None)
  }
};
