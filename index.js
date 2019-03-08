/**
 * This is the main entrypoint to your Probot app
 * @param {import('probot').Application} app
 */
const util = require('util');
const exec = util.promisify(require('child_process').exec);
const git = require('./src/Git');

module.exports = app => {
  // Your code here
  app.log('Yay, the app was loaded!')

  app.log(git.greet("me"))

  app.on('issues.opened', async context => {
    const issueComment = context.issue({ body: 'Thanks for opening this issue!' })
    return context.github.issues.createComment(issueComment)
  })

  app.on('pull_request.opened', async context => {
    const pull_request = context.payload.pull_request;
    const check_options = {
      name: 'robot-caml-jockey',
      head_branch: '',
      head_sha: pull_request.head.sha,
      status: 'in_progress',
      started_at: new Date(Date.now()).toISOString(),
      output: {
        title: 'Running a thing for a bit',
        summary: 'Summarizing whats been going on',
        text: 'This is the text'
      }
    }
    app.log('payload = ' + JSON.stringify(context.payload))

    const result = await context.github.checks.create(context.repo(check_options))
    const id = result.data.id

    app.log('result = ' + JSON.stringify(result))

    const exec_result = await exec('sleep 10 && echo done');

    const check_options2 = {
      ...check_options,
      check_run_id: id,
      status: 'completed',
      completed_at: new Date(Date.now()).toISOString(),
      conclusion: 'success',
      output: {
        title: 'I ran a thing',
        summary: 'It went well',
        text: 'Like, really well.'
      }
    }
    return context.github.checks.update(context.repo(check_options2))

    
  })

  // For more information on building apps:
  // https://probot.github.io/docs/

  // To get your app running against GitHub, see:
  // https://probot.github.io/docs/development/
}
