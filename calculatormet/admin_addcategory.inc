<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Prepare a simple form to add an entry, with all the interesting fields.
 */
function calcmet_form_addcategory($form, &$form_state) {
  $form = array();

  $form['add'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Add a category entry'),
  );
  $form['add']['title'] = array(
    '#type'  => 'textfield',
    '#title' => t('Title'),
    '#size'  => 250,
  );
  $form['add']['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Add'),
  );

  return $form;
}
/**
 * Submit handler for 'add entry' form.
 */
function calcmet_form_addcategory_submit($form, &$form_state) {
  
  // Save the submitted entry.
  $basename = 'calcmetcat';  
  $entry = array(
    'title'    => $form_state['values']['title'],
  );
  $return = calcmet_entry_insert ($basename, $entry);
  if ($return) {
    drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entry, TRUE))));
  }
}