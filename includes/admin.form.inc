<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_bookmark_admin_settings(array $form, array &$form_state) {
  $form = array(
    'list_type' => array(
      '#type' => 'textfield',
      '#title' => t('The name of the type of list.'),
      '#default_value' => variable_get('islandora_bookmark_type', 'bookmark'),
    ),
    'overview_page_elements' => array(
      '#type' => 'textfield',
      '#title' => t('Bookmarks overview table'),
      '#description' => t('Number of Bookmarks shown per page'),
      '#default_value' => variable_get('islandora_bookmark_overview_page_elements', 10),
      '#element_validate' => array('element_validate_integer_positive'),
      '#size' => 4,
    ),
    'detailed_page_elements' => array(
      '#type' => 'textfield',
      '#title' => t('Detailed bookmark table'),
      '#description' => t('Number of objects shown per page'),
      '#default_value' => variable_get('islandora_bookmark_detailed_page_elements', 10),
      '#element_validate' => array('element_validate_integer_positive'),
      '#size' => 4,
    ),
    'create_user_default_lists' => array(
      '#type' => 'checkbox',
      '#title' => t('Create a default list for users?'),
      '#default_value' => variable_get('islandora_bookmark_create_user_default_lists', FALSE),
    ),
    'default_list_name' => array(
      '#type' => 'textfield',
      '#title' => t('Default list name'),
      '#description' => t("The name of the default user list. To use the user's name in the field use '@username'."),
      '#default_value' => variable_get('islandora_bookmark_default_list_name', "@username's Default List"),
      '#states' => array(
        'visible' => array(
          ':input[name="create_user_default_lists"]' => array('checked' => TRUE),
        ),
      ),
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    ),
    'reset' => array(
      '#type' => 'submit',
      '#value' => t('Reset to defaults'),
    ),
  );

  return $form;
}

/**
 * Validation function for the Bookmark admin form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_bookmark_admin_settings_validate(array $form, array &$form_state) {
  if ($form_state['triggering_element']['#id'] != 'edit-reset' && $form_state['values']['create_user_default_lists']) {
    if (empty($form_state['values']['default_list_name'])) {
      form_set_error('default_list_name', t('Please provide a name for default user lists.'));
    }
  }
}

/**
 * Function that sets the Drupal variables with user's input.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_bookmark_admin_settings_submit(array $form, array &$form_state) {
  drupal_set_message(t('The settings have been updated!'));
  $id = $form_state['triggering_element']['#id'];
  switch ($id) {
    case 'edit-submit':
      variable_set('islandora_bookmark_overview_page_elements', $form_state['values']['overview_page_elements']);
      variable_set('islandora_bookmark_detailed_page_elements', $form_state['values']['detailed_page_elements']);
      variable_set('islandora_bookmark_type', $form_state['values']['list_type']);
      variable_set('islandora_bookmark_create_user_default_lists', $form_state['values']['create_user_default_lists']);
      if ($form_state['values']['create_user_default_lists']) {
        variable_set('islandora_bookmark_default_list_name', $form_state['values']['default_list_name']);
      }
      break;

    case 'edit-reset':
      variable_del('islandora_bookmark_overview_page_elements');
      variable_del('islandora_bookmark_detailed_page_elements');
      variable_del('islandora_bookmark_type');
      variable_del('islandora_bookmark_create_user_default_lists');
      variable_del('islandora_bookmark_default_list_name');
      break;
  }
}
