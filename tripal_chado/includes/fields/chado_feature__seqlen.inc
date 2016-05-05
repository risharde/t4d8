<?php
/**
 * Implements hook_info() for fields.
 *
 * This is a hook provided by the tripal_chado module for offloading the
 * hook_field_info() hook for each field to specify.
 */
function chado_feature__seqlen_info() {
  return array(
    'label' => t('Sequence length'),
    'description' => t('A field for calculating the length of a sequence.'),
    'default_widget' => 'chado_feature__seqlen_widget',
    'default_formatter' => 'chado_feature__seqlen_formatter',
    'settings' => array(),
    'storage' => array(
      'type' => 'field_chado_storage',
      'module' => 'tripal_chado',
      'active' => TRUE
    ),
  );
}
/**
 * Implements hook_attach_info().
 *
 * This is a hook provided by the tripal_Chado module. It allows the field
 * to specify which bundles it will attach to and to specify thee settings.
 *
 * @param $entity_type
 * @param $entity
 * @param $term
 *
 * @return
 *   A field array
 */
function chado_feature__seqlen_attach_info($entity_type, $bundle, $target) {
  $field_info = array();

  $table_name = $target['data_table'];
  $type_table = $target['type_table'];
  $type_field = $target['field'];
  $cv_id      = $target['cv_id'];
  $cvterm_id  = $target['cvterm_id'];


  // If  this is not the feature table then we don't want to attach.
  if ($table_name != 'feature') {
    return $field_info;
  }

  $field_info = array(
    'field_name' => 'feature__seqlen',
    'field_type' => 'chado_feature__seqlen',
    'widget_type' => 'chado_feature__seqlen_widget',
    'description' => 'The length of the sequence (residues).',
    'label' => 'Sequence Length',
    'is_required' => 0,
    'storage' => 'field_chado_storage',
    'widget_settings' => array(
      'display_label' => 1
    ),
    'field_settings' => array(
      'chado_table' => $table_name,
      'chado_column' => 'seqlen',
      'semantic_web' => array(
        'name' => '',
        'accession' => '',
        'ns' => '',
        'nsurl' => '',
      ),
    ),
  );

  return $field_info;
}
/**
 * Implements hook_widget_info.
 *
 * This is a hook provided by the tripal_chado module for offloading
 * the hook_field_widget_info() hook for each field to specify.
 */
function chado_feature__seqlen_widget_info() {
  return array(
    'label' => t('Sequence Length'),
    'field types' => array('chado_feature__seqlen'),
  );
}
/**
 * Implements hook_formatter_info.
 *
 * This is a hook provided by the tripal_chado module for
 * offloading the hook_field_formatter_info() for each field
 * to specify.
 *
 */
function chado_feature__seqlen_formatter_info() {
  return array(
    'label' => t('Residues Length'),
    'field types' => array('chado_feature__seqlen'),
    'settings' => array(
    ),
  );
}

/**
 *
 * @param unknown $entity_type
 * @param unknown $entity
 * @param unknown $field
 * @param unknown $instance
 * @param unknown $langcode
 * @param unknown $items
 * @param unknown $display
 */
function chado_feature__seqlen_formatter(&$element, $entity_type, $entity, $field,
    $instance, $langcode, $items, $display) {

  foreach ($items as $delta => $item) {
    $content = key_exists('value', $item) ? $item['value'] : '';
    $element[$delta] = array(
      // We create a render array to produce the desired markup,
      '#type' => 'markup',
      '#markup' => $content,
    );
  }
}

/**
 *
 * @param unknown $field_name
 * @param unknown $widget
 * @param unknown $form
 * @param unknown $form_state
 * @param unknown $field
 * @param unknown $instance
 * @param unknown $langcode
 * @param unknown $items
 * @param unknown $delta
 * @param unknown $element
 */
function chado_feature__seqlen_widget(&$widget, $form, $form_state, $field, $instance, $langcode, $items, $delta, $element) {

  $widget['value'] =  array(
    '#type' => 'hidden',
    '#title' => $element['#title'],
    '#description' => $element['#description'],
    '#weight' => isset($element['#weight']) ? $element['#weight'] : 0,
    '#delta' => $delta,
    '#element_validate' => array('chado_feature__seqlen_widget_validate'),
  );
}
/**
 * Callback function for validating the chado_feature__seqlen_widget.
 */
function chado_feature__seqlen_widget_validate($element, &$form_state) {
  $field_name = $element['#parents'][0];

  // Get the residues so we can calculate teh length.
  $residues = tripal_chado_get_field_form_values('feature__residues', $form_state);

  // Remove any white spaces.
  if ($residues) {
    $residues = preg_replace('/\s/', '', $residues);
    tripal_chado_set_field_form_values($field_name, $form_state, strlen($residues));
  }
  else {
    // Otherwise, remove the md5 value
    tripal_chado_set_field_form_values($field_name, $form_state, '__NULL__');
  }
}