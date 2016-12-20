<?php
$prefix = '[Argument & Computation] ';

define ( 'EIC_ROLE' , 'EditorInChief' );
define ( 'EA_ROLE' , 'Assistant Editor' );

define('BIDDING_SUBJECT', $prefix.' Bidding for a new submission #{{tracking_number}}');
define('BIDDING_MESSAGE', 'Dear Editorial Board Members,

Please reply to this message if you are interested either in serving as Handling Editor or in reviewing the following manuscript in a reasonable time.

As always, we cannot assign reviewers to this paper until we identify a Handling Editor. Please reply to <contact-ao-journal@iossubmissions.com>.

Thanks,
The Editors in Chief

Title: {{title}}
Tracking number: #{{tracking_number}}
Abstract:{{abstract}}

    ');
define('GENERIC_SUB', $prefix. ' REG: {{tracking_number}}');
define('GENERIC_MSG', '

Paper Details:
Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}

    ');
//Email to Author for new submission
define ('AUTHOR_SUBMISSION_SUBJECT', $prefix . 'Your submission to the Semantic Web journal, #{{tracking_number}}');
define ('AUTHOR_SUBMISSION_MESSAGE', 'Dear {{author}},

Thank you for submitting your paper to Argument-and-computation. It has been assigned tracking number {{tracking_number}}. We will start reviewing within a few days, and you will then be able to obtain the history and current status of your manuscript, by visiting the address presented below.

{{direct_url}}

Sincerely,

Argument & Computation Editorial Office
');

//Email to newly created user as Author for new submission
define ('AUTHOR_SUBMISSION_NEW', $prefix . 'Your submission to the Semantic Web journal, #{{tracking_number}}');
define ('AUTHOR_SUBMISSION_NEW_MSG', 'Dear {{author}},

Thank you for submitting your paper to Argument & Computation. It has been assigned tracking number {{tracking_number}}. We will start reviewing within a few days, and you will then be able to obtain the history and current status of your manuscript, by visiting the address presented below.

For future steps in the review process, we have created an account for you on the journal homepage, login: {{login}}. We have sent you a separate email to reset your password. If you already had an account on the Argument & Computation website, please let us know by email to contact@semantic-web-journal.net and we will correct our records.

You can also directly access the paper by using : {{direct_url}}
Sincerely,

Argument & Computation Editorial Office
');

//Email to EIC notifying new submission
define ('SUBMISSION_EIC_SUB', $prefix . 'Paper submission');
define ('SUBMISSION_EIC_MSG', 'A paper has been submitted to the Argument & Computation, which requires processing. Please login and visit the new submissions link.

Paper Details:

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}

Argument & Computation'
);

//Email to editors for revising decision letter
define ('REVISE_DEC_LETTER_SUB', $prefix . 'Review Decision Letter for, #{{tracking_number}}');
define ('REVISE_DEC_LETTER_MSG', 'Dear Editor,

Please revise the decision letter for the below paper.

Paper Details:

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}

http://www.semantic-web-journal.net/'
);

define ('SUBMISSION_EDITOR_SUB', $prefix . 'Paper assigned to you, #{{tracking_number}}');
define ('SUBMISSION_EDITOR_MSG', 'Dear {{editor}},

We just assigned a paper to you as responsible editor. Please have a look and let us know immediately in case you are unable to take care of it as soon as possible. You can login and follow the "Papers to manage" link on the left sidebar to see this submission.

Paper Details:

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}


As a reminder: our guidelines for editors can be found at http://www.semantic-web-journal.net/howtoeditors

Thank you very much for your continued support.

Best Regards,

Pascal Hitzler and Krzysztof Janowicz
Editors-in-Chief, Semantic Web journal
contact@semantic-web-journal.net
http://www.semantic-web-journal.net/'
);

//NOT USED ANYMORE, email to author after Responsible Editor is assigned.
define ('SUBMISSION_AUTHOR_APR_SUB',$prefix . 'Your submitted paper, #{{tracking_number}}');
define ('SUBMISSION_AUTHOR_APR_MSG', 'Dear {{author}},

Thank you for submitting your paper to the Semantic Web journal. We have initiated reviewing of your paper, and you will be notified of the progress. You can now find your paper listed at http://www.semantic-web-journal.net/underreview as a paper under review.

Best Regards,

Pascal Hitzler and Krzysztof Janowicz
Editors-in-Chief, Semantic Web journal
contact@semantic-web-journal.net
http://www.semantic-web-journal.net/'
);

// Email to reviewer for assignment (existing accounts)
define('REVIEWER_ASSIGNMENT_SUB', $prefix . 'Request to review paper, #{{tracking_number}}');
define('REVIEWER_ASSIGNMENT_MSG','Dear {{reviewer}},

A manuscript was recently submitted to the Semantic Web journal:

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})

If interested and available, would you be so kind as to provide a timely review of this manuscript? If so, I ask that it be returned within 30 days. If you think you need more time for the review, please let me know. To access the paper and provide your review or to confirm or reject this review request please visit {{url}}. Note that you must be logged in with your existing user account to do so.

If you agree to act as a reviewer, please make sure you are aware of the instructions for reviewers at {{site_url}}/reviewers - in particular note that SWJ has an open and transparent review process, i.e., your review will be made publicly available on the journal website. The Semantic Web journal by default requests non-anonymous reviews. However, you can choose to remain anonymous, in this case please declare this by indicating your choice on the review form.

On http://www.semantic-web-journal.net/reviewers we list the different types of submissions which can be made to the journal. Each type has different review criteria. Please take these review criteria explicitly into account when you write your review. If the submission is for a special call or special issue, then please take note of the corresponding call for papers. If you are uncertain about this specific paper, please contact us.

Thank you for your time.

Sincerely,
{{editor}}'); ////////////////////////////////////////////////////////


// Email to reviewer for assignment (new accounts)
//Called from invite reviewer
define('REVIEWER_ASSIGNMENT_SUB_NEW', $prefix . 'Request to review paper, #{{tracking_number}}');
define('REVIEWER_ASSIGNMENT_MSG_NEW','Dear {{reviewer}},

A manuscript was recently submitted to the Semantic Web journal:

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})

If interested and available, would you be so kind as to provide a timely review of this manuscript? If so, I ask that it be returned within 30 days. If you think you need more time for the review, please let me know.

For the reviewing, a user account has been created for you. For security reasons, it is required that you change your initial password. A separate email has been sent to you that contains a password reset link.  To confirm or deny this request, please visit the paper on the website {{url}}. For this, you need to log in as user to the site.

If you agree to act as a reviewer, please make sure you are aware of the instructions for reviewers at http://www.semantic-web-journal.net/reviewers - in particular note that SWJ has an open and transparent review process, i.e., your review will be made publicly available on the journal website. The Semantic Web journal by default requests non-anonymous reviews. However, you can choose to remain anonymous, in this case please declare this by indicating your choice on the review form.

On http://www.semantic-web-journal.net/reviewers we list the different types of submissions which can be made to the journal. Each type has different review criteria. Please take these review criteria explicitly into account when you write your review. If the submission is for a special call or special issue, then please take note of the corresponding call for papers. If you are uncertain about this specific paper, please contact us.

Thank you for your time.

Sincerely,
{{editor}}');


//Email to Eics and Editor. Review received.
define('REV_SUBMIT_SUB', $prefix . 'Review received, #{{tracking_number}}');
define('REVIEW_SUBMIT_MSG','A review has been provided for a paper which was assigned to you.

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})
Review submitted by: {{reviewer}}

Review Details:

{{review}}

You can access the paper by logging in as editorial board member on {{site_url}}');

define('REV_DEC_EDITOR_SUB', $prefix . 'Decision on paper required, #{{tracking_number}}');
define('REV_DEC_EDITOR_MSG','
Dear {{editor}},

One of the papers assigned to you has now received the minimum number of required reviews. Please check if a decision on the paper can now be reached, and if so, please write a corresponding decision letter. Please discuss with the editors-in-chief in case there are any doubts about the appropriate decision.

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})

You find the paper by logging in as editorial board member on http://www.semantic-web-journal.net/');

//Notification once three reviews have been submitted.
define('REV_DEC_EIC_SUB', $prefix . 'Decision letter needed, #{{tracking_number}}');
define('REV_DEC_EIC_MSG','This paper has now received the minimum number of required reviews.

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})');

//Notification to EIC when decision letter has been submitted by Editor.
define('REV_DEC_LETTER_SUB', $prefix . 'Decision letter drafted, #{{tracking_number}}');
define('REV_DEC_LETTER_MSG','A decision letter for this paper has been drafted.

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})');

//Decision letter sent to the authors
define('REV_DEC_APR_SUB', $prefix . 'Decision letter, #{{tracking_number}}');
define('REV_DEC_APR_MSG', 'Dear Author,
We have reached a decision for your paper. Please find below the details.

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})

Decision Letter: {{decision_letter}}
');

//Appreciation email to reviewers for submitting the review. Notification sent after approval of decision.
define('REV_DEC_APR_REV_SUB', $prefix . 'Thank you for your support');
define('REV_DEC_APR_REV_MSG','Dear {{reviewer}},

We have reached a decision regarding paper {{title}} which you helped reviewing. Your input was very valuable for us. You can see all reviews and the decision taken at {{url}}.

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})

Best Regards,

Pascal Hitzler and Krzysztof Janowicz
Editors-in-Chief, Semantic Web journal
contact@semantic-web-journal.net
http://www.semantic-web-journal.net/');

//Letter sent to Editor after decision has been approved.
define('REV_DEC_APR_EDITOR_SUB', $prefix . 'Decision letter sent, #{{tracking_number}}');
define('REV_DEC_APR_EDITOR_MSG','Decision letter sent, thank you for your continued support.

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Tracking number: {{tracking_number}}
Assigned editor: {{editor}} ({{editor_email}})

Best Regards,

Pascal Hitzler and Krzysztof Janowicz
Editors-in-Chief, Semantic Web journal
contact@semantic-web-journal.net
http://www.semantic-web-journal.net/');

//Notification to Eic and Editor once the reviewer accepts the invitation
define('REV_ACCEPT_SUB', $prefix . 'Reviewer has accepted invitation to review #{{tracking_number}}');
define('REV_ACCEPT_MSG', '{{reviewer}} has agreed to review "{{title}}."

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Assigned editor: {{editor}} ({{editor_email}})
Tracking number: {{tracking_number}}');

//Notification to Eic and Editor once the reviewer rejects the invitation.
define('REV_REJECT_SUB', $prefix . 'Reviewer has declined invitation to review #{{tracking_number}}');
define('REV_REJECT_MSG', '{{reviewer}} has declined to review "{{title}}."

Reason: {{content}}

Paper Details:

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Assigned editor: {{editor}} ({{editor_email}})
Tracking number: {{tracking_number}}');

define('REV_REMINDER_SUB', $prefix. 'Review Reminder #{{tracking_number}}');
define('REV_REMINDER_MSG',
'Dear {{reviewer}},

We would like to remind you of a pending review for the following paper, which was submitted to the Argument & Computation:

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Assigned editor: {{editor}} ({{editor_email}})
Tracking number: {{tracking_number}}

To obtain the paper and enter the review, please go to {{direct_url}}

Please do not hesitate to contact me if you have any questions.

{{editor}}'
);

define('EDITOR_REMINDER_SUB', $prefix. 'Editorial Reminder #{{tracking_number}}');
define('EDITOR_REMINDER_MSG',
'Dear {{editor}},

Some time ago, the manuscript {{title}} has been assigned to you. Since then, according to what results from our journal management system, no reviewers have been appointed. We assume you have been too busy, but we remind you that reviewers’ assignment is a preliminary, necessary step to trigger the whole handling process.

We would appreciate if you take action as soon as possible

You can access the system through the following webpage:

{{url}}

and, after having inserted your login and password, you can have a look at your actions needed.
Don’t hesitate to contact us in case you have forgotten your login and/or password or if you need any help with the system.

Best Regards,
the Editorial Office of Argument & Computation'

);

define('SWJ_NOTICE','
');

//Notification to Eic when editor rejects invitation.
define('EDITOR_REJECT_SUB', $prefix . 'Editor Decline #{{tracking_number}}');
define('EDITOR_REJECT_MSG', '{{editor}} has declined to be the editor of "{{title}}."

Reason: {{content}}

Paper Details:

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Assigned editor: {{editor}} ({{editor_email}})
Tracking number: {{tracking_number}}');

define('EDITOR_ACCEPT_SUB', $prefix . 'Editor has agreed #{{tracking_number}}');
define('EDITOR_ACCEPT_MSG', '{{editor}} has agreed to perform editorial duties for "{{title}}."

Authors: {{authors}}
Title: {{title}}
Submission Type: {{submission_type}}
URL: {{url}}
Assigned editor: {{editor}} ({{editor_email}})
Tracking number: {{tracking_number}}');

//EOF







