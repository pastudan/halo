#!/usr/bin/env python3
"""Track A grokB w5c: more network message-handler Unicorn proves."""
from __future__ import annotations
import json, os, re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from lift_inventory_batch4 import find_naked_block
from prove_inventory_batch4 import ensure_oracle, flip_kb
from tu_compile import docker_compile
from unicorn_c_campaign import KB_PATH, append_ledger, clear_pass, count_ported
from lift_grok_w4 import audit_naked_true, cast_stale

LIFTS = {}
MAX_SRC_CHUNK = 3600

def L(addr, source, name, body, decl):
    LIFTS[addr] = (source, name, body.strip()+"\n", decl)

L(0x80CA0, "networking/message_header.c", "create_message", """
/* create_message (0x80ca0) — readable C lift. */
int create_message(int type, int payload, unsigned int payload_len, int buffer, unsigned short buffer_size)
{
  unsigned short total;
  void *buf;

  total = (unsigned short)(payload_len + 2);
  buf = (void *)buffer;
  if (buf == 0) {
    buf = debug_malloc((unsigned int)(short)total, 0, (const char *)0x265ccc, 0x2e);
  } else if ((int)buffer_size < (int)(short)total) {
    display_assert((const char *)0x265d24, (const char *)0x265ccc, 0x29, 1);
    system_exit(-1);
  }
  if (buf != 0) {
    build_message_header((unsigned short *)buf, total, (unsigned char)type, 0);
    if (payload != 0)
      csmemcpy((char *)buf + 2, (void *)payload, (unsigned short)payload_len);
  }
  return (int)buf;
}
""", "int create_message(int type, int payload, unsigned int payload_len, int buffer, unsigned short buffer_size);")

L(0x12F0D0, "networking/network_server_manager.c", "FUN_0012f0d0", """
/* FUN_0012f0d0 (0x12f0d0) — readable C lift. */
bool FUN_0012f0d0(int server, int machine, void *message_data, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  char value[0x100];
  bool ok;

  if (network_game_server_get_state(server, (short *)0) != 0) {
    network_game_log((const char *)0x298a78);
    return 1;
  }
  size_left = message_size - 2;
  field_size = 0x13;
  field_count = 1;
  ok = FUN_0012bce0((int)value, (int)((char *)message_data + 2), (short *)&size_left, &field_size, &field_count, 3);
  if (ok) {
    FUN_0012cbe0((void *)server, machine, value);
    return 1;
  }
  network_game_log((const char *)0x298ae0);
  return 1;
}
""", "bool FUN_0012f0d0(int server@<esi>, int machine, void *message_data, int message_size);")

L(0x12F290, "networking/network_server_manager.c", "FUN_0012f290", """
/* FUN_0012f290 (0x12f290) — readable C lift. */
bool FUN_0012f290(int server, int machine, void *message_data, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  char value[0x20];
  bool ok;

  if (network_game_server_get_state(server, (short *)0) != 2) {
    network_game_log((const char *)0x298c70);
    return 1;
  }
  size_left = message_size - 2;
  field_size = 0x20;
  field_count = 1;
  ok = FUN_0012bce0((int)value, (int)((char *)message_data + 2), (short *)&size_left, &field_size, &field_count, 7);
  if (ok) {
    if (!FUN_0012c920((void *)server, machine, value))
      network_game_log((const char *)0x298d28);
    return 1;
  }
  network_game_log((const char *)0x298cd8);
  return 1;
}
""", "bool FUN_0012f290(int server@<esi>, int machine, void *message_data, int message_size);")

L(0x1273A0, "networking/network_client_manager.c", "FUN_001273a0", """
/* FUN_001273a0 (0x1273a0) — readable C lift. */
char FUN_001273a0(void *client, void *source_address, void *message, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  char value[8];
  bool ok;

  if (!FUN_00124d50(client, source_address) || network_game_client_get_state(client, (void *)0) != 1) {
    network_game_log((const char *)0x2934e8);
    return 0;
  }
  size_left = message_size - 2;
  field_size = 4;
  field_count = 1;
  ok = FUN_0012bce0((int)value, (int)((char *)message + 2), (short *)&size_left, &field_size, &field_count, 2);
  if (ok) {
    network_game_client_accepted_into_game(client, source_address, value);
    return 1;
  }
  network_game_log((const char *)0x293548);
  return 0;
}
""", "char FUN_001273a0(void *client@<esi>, void *source_address@<edi>, void *message, int message_size);")

L(0x127440, "networking/network_client_manager.c", "FUN_00127440", """
/* FUN_00127440 (0x127440) — readable C lift. */
char FUN_00127440(void *client, void *source_address, void *message, int message_size)
{
  int size_left;
  short field_size;
  short field_count;
  int value;
  bool ok;

  if (!FUN_00124d50(client, source_address) || network_game_client_get_state(client, (void *)0) != 1) {
    network_game_log((const char *)0x293588);
    return 0;
  }
  size_left = message_size - 2;
  field_size = 5;
  field_count = 1;
  ok = FUN_0012bce0((int)&value, (int)((char *)message + 2), (short *)&size_left, &field_size, &field_count, 2);
  if (ok) {
    FUN_001271a0(client, source_address, value);
    return 1;
  }
  network_game_log((const char *)0x2935e8);
  return 0;
}
""", "char FUN_00127440(void *client@<esi>, void *source_address@<edi>, void *message, int message_size);")

def apply_one(addr):
    source, name, body, decl = LIFTS[addr]
    sp = ROOT / "src" / "halo" / source
    text = sp.read_text(encoding="utf-8", errors="replace")
    if re.search(rf"0x{addr:x}[^\n]*readable C lift", text, re.I):
        return True, "already", text
    span = find_naked_block(text, name, addr)
    if not span:
        return False, "locate", text
    if len(text[span[0]:span[1]].encode()) > MAX_SRC_CHUNK:
        return False, "too_big", text
    new_text = text[:span[0]] + body + "\n" + text[span[1]:]
    new_text = cast_stale(new_text, {name})
    sp.write_text(new_text, encoding="utf-8")
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl if decl.endswith(";") else decl + ";"
                fn["name"] = name
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    if not docker_compile(source):
        sp.write_text(text, encoding="utf-8")
        return False, "compile", text
    return True, "ok", text

def run_uni(name, addr, seeds=100, timeout=70.0):
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{seeds}.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
    cmd = [sys.executable, str(ROOT/"tools/equivalence/unicorn_diff.py"), name,
           "--allow-stubs","--no-stub-arg-trace","--no-stub-conv-check","--float-tolerance","32",
           "--seeds",str(seeds),"-q","--output-json",str(outj)]
    env = os.environ.copy(); env["BIPED_SIBLING_RESOLVE"]="1"
    try:
        proc = subprocess.run(cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout, env=env)
    except subprocess.TimeoutExpired:
        return {"passed":0,"failed":0,"errors":1,"tail":"TIMEOUT"}
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    p=f=e=None
    if m: p,f,e=map(int,m.groups())
    return {"passed":p,"failed":f,"errors":e,"tail":text[-400:]}

def commit_push(flips, touched):
    subprocess.run(["git","checkout","--","tools/equivalence/leaf_cache.json"], cwd=ROOT, check=False)
    files = ["kb.json","scripts/lift_grok_w5c.py"] + [str(p.relative_to(ROOT)) for p in sorted(touched)]
    for f in files:
        subprocess.run(["git","add","--",f], cwd=ROOT, check=False)
    msg = f"lift(track-a): {' '.join(flips[:6])} Unicorn-prove (ported:true)."
    r = subprocess.run(["git","commit","-m",msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr); return
    subprocess.run(["git","fetch","pastudan","track-a-collision-bsp"], cwd=ROOT, capture_output=True)
    rb = subprocess.run(["git","rebase","pastudan/track-a-collision-bsp"], cwd=ROOT, capture_output=True, text=True)
    if rb.returncode != 0:
        print("rebase conflict", rb.stdout, rb.stderr)
        subprocess.run(["git","rebase","--abort"], cwd=ROOT, capture_output=True); return
    if audit_naked_true():
        print("ABORT naked-true", audit_naked_true()[:5]); return
    r = subprocess.run(["git","push","pastudan","HEAD:track-a-collision-bsp"], cwd=ROOT, capture_output=True, text=True)
    print("PUSH", r.returncode, (r.stderr or r.stdout)[-400:])

def main():
    order = [0x80CA0, 0x12F0D0, 0x12F290, 0x1273A0, 0x127440]
    true0,_ = count_ported(json.loads(KB_PATH.read_text()))
    print(f"start true={true0}", flush=True)
    flips=[]; touched=set()
    for addr in order:
        source,name,_,_ = LIFTS[addr]
        kb=json.loads(KB_PATH.read_text())
        if any(fn.get("addr") and int(fn["addr"],16)==addr and fn.get("ported") is True for o in kb.get("objects",[]) for fn in o.get("functions") or []):
            print(f"\n== {hex(addr)} already true ==", flush=True); continue
        print(f"\n== {hex(addr)} {name} ==", flush=True)
        ok,err,orig=apply_one(addr)
        if not ok and err!="already":
            print("  apply FAIL", err, flush=True); continue
        if err=="already" and not docker_compile(source):
            print("  compile FAIL", flush=True); continue
        if not ensure_oracle(addr):
            print("  oracle FAIL", flush=True)
            if err!="already": (ROOT/"src"/"halo"/source).write_text(orig)
            continue
        res=run_uni(name,addr)
        if not clear_pass(res,100):
            res2=run_uni(hex(addr),addr)
            if (res2.get("passed") or 0) >= (res.get("passed") or 0): res=res2
        okp=clear_pass(res,100)
        print(f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} ok={okp}", flush=True)
        append_ledger({"addr":hex(addr),"name":name,"ok":okp,"phase":"lift_grok_w5c","passed":res.get("passed"),"failed":res.get("failed"),"errors":res.get("errors")})
        if not okp:
            print("  REVERT", (res.get("tail") or "")[-180:], flush=True)
            if err!="already": (ROOT/"src"/"halo"/source).write_text(orig)
            continue
        kb=json.loads(KB_PATH.read_text())
        if flip_kb(kb, addr):
            KB_PATH.write_text(json.dumps(kb, indent=2)+"\n")
            flips.append(name); touched.add(ROOT/"src"/"halo"/source)
            print(f"  FLIP total={len(flips)}", flush=True)
    print("FLIPS", flips, flush=True)
    if flips and not audit_naked_true():
        commit_push(flips, touched)
    true1,_=count_ported(json.loads(KB_PATH.read_text()))
    print(f"DONE proven={len(flips)} true={true1} (+{true1-true0})", flush=True)
    return 0 if flips else 1

if __name__ == "__main__":
    raise SystemExit(main())
