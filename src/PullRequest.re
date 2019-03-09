[@bs.deriving abstract]
type user = {
    login : string,
    id: int,
    node_id: string,
    avatar_url: string
};

[@bs.deriving abstract]
type repository = {
    id : int,
    node_id : string,
    name: string,
    full_name: string,
    owner: user,
    private: bool,
    html_url: string,
    clone_url: string,
};

[@bs.deriving abstract]
type head_type = {
    label: string,
    ref: string,
    sha: string,
    user: user,
    repo : repository
};

[@bs.deriving abstract]
type pull_request = {
    url: string,
    id: int,
    node_id: string,
    html_url: string,
    diff_url: string,
    patch_url: string,
    issue_url: string,
    number: int,
    state: string,
    locked: bool,
    title: string,
    user: user,
    body: string,
    created_at: option(string),
    updated_at: option(string),
    closed_at: option(string),
    merged_at: option(string),
    merge_commit_sha: option(string),
    assignee: option(user), 
    assignees: list(user), 
    requested_reviewers: list(user), 
    head : head_type,
};

[@bs.deriving abstract]
type installation = {
    id : int
};
[@bs.deriving abstract]
type context = {
    action: string,
    number: int,
    pull_request : pull_request,
    repository: repository,
    sender : user,
    installation : installation
};

let pr = (context,log : ((. string) => unit)) => {
    let repository = repositoryGet(context);
    let name = nameGet(repository)
    Scratch.create_scratch("user",name,numberGet(context));
    log(. Printf.sprintf("name=%s number=%d",name,numberGet(context)))
};