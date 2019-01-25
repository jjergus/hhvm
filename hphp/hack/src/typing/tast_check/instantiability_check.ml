(**
 * Copyright (c) 2018, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the "hack" directory of this source tree.
 *
 *)

open Core_kernel
open Tast
module ShapeMap = Aast.ShapeMap
module SN = Naming_special_names
module Cls = Typing_classes_heap

let validate_classname (pos, hint) =
  match hint with
    | Aast.Happly _
    | Aast.Hthis
    | Aast.Hany
    | Aast.Hmixed
    | Aast.Hnonnull
    | Aast.Habstr _
    | Aast.Haccess _
    | Aast.Hdynamic
    | Aast.Hsoft _
    | Aast.Hreified _ ->
      ()
    | Aast.Htuple _
    | Aast.Harray _
    | Aast.Hdarray _
    | Aast.Hvarray _
    | Aast.Hvarray_or_darray _
    | Aast.Hprim _
    | Aast.Hoption _
    | Aast.Hfun _
    | Aast.Hshape _ ->
      Errors.invalid_classname pos

let rec check_hint env (pos, hint) =
  match hint with
  | Aast.Happly ((_, class_id), tal) ->
    begin match Tast_env.get_class env class_id with
    | Some cls when
      let kind = Cls.kind cls in
      let tc_name = Cls.name cls in
      (kind = Ast.Ctrait || kind = Ast.Cabstract && Cls.final cls)
      && tc_name <> SN.Collections.cDict
      && tc_name <> SN.Collections.cKeyset
      && tc_name <> SN.Collections.cVec ->
      let tc_pos = Cls.pos cls in
      let tc_name = Cls.name cls in
      Errors.uninstantiable_class pos tc_pos tc_name []
    | _ -> ()
    end;
    if class_id = SN.Classes.cClassname
    then Option.iter (List.hd tal) validate_classname
    else List.iter tal (check_hint env)
  | Aast.Harray (hopt1, hopt2) ->
    Option.iter hopt1 (check_hint env);
    Option.iter hopt2 (check_hint env);
  | Aast.Hdarray (h1, h2) ->
    check_hint env h1;
    check_hint env h2
  | Aast.Hshape hm ->
    check_shape env hm
  | Aast.Haccess (h, ids) ->
    check_access env h ids
  | Aast.Hvarray_or_darray h
  | Aast.Hvarray h
  | Aast.Hoption h
  | Aast.Hsoft h
  | Aast.Hreified h ->
    check_hint env h
  | Aast.Habstr _
  | Aast.Hprim _
  | Aast.Hany
  | Aast.Hdynamic
  | Aast.Hnonnull
  | Aast.Hmixed
  | Aast.Hthis ->
    ()
  | Aast.Hfun (_, _, hl, _, _, _, h, _) ->
    List.iter hl (check_hint env);
    check_hint env h
  | Aast.Htuple hl ->
    List.iter hl (check_hint env)

and check_shape env Aast.{ nsi_allows_unknown_fields=_; nsi_field_map } =
  ShapeMap.iter (fun _ v -> check_hint env v.Aast.sfi_hint) nsi_field_map

(* Need to skip the root of the Haccess element *)
and check_access env h _ =
  match h with
  | _, Aast.Happly (_, hl) ->
    List.iter hl (check_hint env)
  | _ -> check_hint env h

let check_tparams env tparams =
  List.iter tparams ~f:begin fun t ->
    List.iter t.tp_constraints ~f:begin fun (_ck, h) -> check_hint env h end
  end

let handler = object
  inherit Tast_visitor.handler_base
end
