let scratch_root = "/local/scratch/probot";

[@bs.val] [@bs.module "fs"]
external mkdirSync : string => unit = "";


let with_scratch = (user,repo,pr,f) => {
    let path = Printf.sprintf("%s/%s/%s/%d",scratch_root,user,repo,pr);
    Node.Child_process.(execSync("mkdir -p " ++ path, option ())) |> ignore; 
    try {
        Node.Process.process##chdir(path);
        f ()
    } {
    | e => {
        Node.Child_process.(execSync("rm -rf " ++ path, option ())) |> ignore;
        raise e
        }
    }
}
