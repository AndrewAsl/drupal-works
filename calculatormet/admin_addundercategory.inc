<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Prepare a simple form to add an entry, with all the interesting fields.
 */
function calcmet_form_addundercategory($form, &$form_state) {
  $form = array();
  $entries = calcmet_load('calcmetcat');
  foreach ($entries as $entry) {
    $options[$entry->ccid] = t("@ccid: @title",
      array(
        '@ccid' => $entry->ccid,
        '@title' => $entry->title,
      )
    );
  }
  ksort($options);
  firep($options);
  
  $form['addundercat'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Add a under category entry'),
  );
  $form['addundercat']['ccid'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t('Choose category'),
    //'#default_value' => $default_entry->pid,
    //'#ajax' => array(
    //  'wrapper' => 'updateform',
    //  'callback' => 'dbtng_example_form_update_callback',
    //),
  );
  $form['addundercat']['title'] = array(
    '#type'  => 'textfield',
    '#title' => t('Title'),
    '#size'  => 250,
  );
  $form['addundercat']['image'] = array(
    '#type'  => 'textfield',
    '#title' => t('Изображение'),
    '#size'  => 250,
  );
  $form['addundercat']['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Add'),
  );

  return $form;
}
function calcmet_form_addundercategory_submit($form, &$form_state) {
  
  // Save the submitted entry.
  $basename = 'calcmetundercat';  
  $entry = array(
    'ccid'  => $form_state['values']['ccid'],  
    'title' => $form_state['values']['title'],
    'image' => $form_state['values']['image'], 
  );
  $return = calcmet_entry_insert ($basename, $entry);
  if ($return) {
    drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entry, TRUE))));
  }
}
