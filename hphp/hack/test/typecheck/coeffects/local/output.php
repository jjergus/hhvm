<?hh

function allowed()[\HH\Capabilities\Output]: void {
  echo("good");
  echo "good";
}

function disallowed0()[]: void {
  echo("bad - pure context");
  echo "bad - pure context";
}

function disallowed2()[local]: void {
  echo 42; // bad: local does not include IO
}

function allowed_by_default(): void {
  echo("good");
  echo "good";
}
