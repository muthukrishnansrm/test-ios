<?php

class VanillaForumService {

  private static function headers($params) {
    return array(
      'cache_default_override' => TRUE,
      'cache_default_time' => 30,
      'headers' => array('Content-Type' => 'application/json'),
      'endpoint' => variable_get('orchid_vanilla_url', ''),
      'query' => array_merge(array(
        'access_token' => variable_get('vanilla_api_key'),
        $params
      )),
    );
  }

  private static function rest_get($url, $params) {
    return json_decode(restclient_get($url, self::headers($params))->data, TRUE);
  }

  private static function rest_post($url, $params, $body) {
    return restclient_post(
      $url,
      self::headers($params) +
      array('body' => json_encode($body))
    )->data;
  }

  public static function update_profile($profile) {
    return self::rest_post('api/v1/users/notifications.json', array('User.email' => $profile->mail), array(
      'Email.Mention' => $profile->field_email_mention[LANGUAGE_NONE][0]['value'],
      'Popup.Mention' => $profile->field_popup_mention[LANGUAGE_NONE][0]['value'],
      'Email.Badge' => $profile->field_email_badge[LANGUAGE_NONE][0]['value'],
      'Popup.Badge' => $profile->field_popup_badge[LANGUAGE_NONE][0]['value'],
      'Email.WallComment' => $profile->field_email_wallcomment[LANGUAGE_NONE][0]['value'],
      'Popup.WallComment' => $profile->field_popup_wallcomment[LANGUAGE_NONE][0]['value'],
      'Email.ActivityComment' => $profile->field_email_activitycomment[LANGUAGE_NONE][0]['value'],
      'Popup.ActivityComment' => $profile->field_popup_activitycomment[LANGUAGE_NONE][0]['value'],
      'Email.ConversationMessage' => $profile->field_email_conversationmessage[LANGUAGE_NONE][0]['value'],
      'Popup.ConversationMessage' => $profile->field_popup_conversationmessage[LANGUAGE_NONE][0]['value'],
      'Email.DiscussionComment' => $profile->field_email_discussioncomment[LANGUAGE_NONE][0]['value'],
      'Popup.DiscussionComment' => $profile->field_popup_discussioncomment[LANGUAGE_NONE][0]['value'],
      'Email.BookmarkComment' => $profile->field_email_bookmarkcomment[LANGUAGE_NONE][0]['value'],
      'Popup.BookmarkComment' => $profile->field_popup_bookmarkcomment[LANGUAGE_NONE][0]['value'],
      'Email.BadgeRequest' => $profile->field_email_badgerequest[LANGUAGE_NONE][0]['value'],
      'Popup.BadgeRequest' => $profile->field_popup_badgerequest[LANGUAGE_NONE][0]['value'],
    ));
  }

  public static function get_profile_data($email) {
    return self::rest_get('api/v1/users/get.json', array('User.email' => $email));
  }

  public static function get_discussions($page) {
    return self::rest_get('api/v1/discussions/list.json', array('page' => $page));
  }

  public static function get_categories() {
    return self::rest_get('api/v1/categories.json', array());
  }

  public static function get_bookmarks($vanilla_sso) {
    return self::rest_get('api/v1/discussions/bookmarked.json', array(
      'sso' => $vanilla_sso,
    ));
  }

  public static function remove_bookmark($vanilla_sso, $id, $email) {
    return self::rest_post('api/v1/discussions/bookmark.json', array(
      'sso' => $vanilla_sso,
    ), array(
      'Discussion.ID' => $id,
      'Bookmark' => FALSE,
      'User.Email' => $email
    ));
  }
}
